#include <QtGui/qvalidator.h>
#include "CyclicCodesWidget.h"

CyclicCodesWidget::CyclicCodesWidget(ICyclicCodesLab &lab) : lab(&lab) {
    qRegisterMetaType<std::string>();
    qRegisterMetaType<CyclicLabResult>();

    eventHandler = new EventHandler(this);
    lab.setEventListener(eventHandler);

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateResult()));

    createLayouts();
}

CyclicCodesWidget::~CyclicCodesWidget() {
    delete eventHandler;
}

void CyclicCodesWidget::createLayouts() {
    QGridLayout *grid = new QGridLayout();

    QGroupBox *inputBox = createInputLayout();
    QGroupBox *commandLayout = createCommandLayout();
    QGroupBox *outputLayout = createOutputLayout();

    inputBox->setMinimumWidth(400);
    inputBox->setMaximumWidth(600);
    commandLayout->setMinimumWidth(400);
    commandLayout->setMaximumWidth(600);
    outputLayout->setMinimumWidth(300);
    outputLayout->setMaximumWidth(500);

    grid->addWidget(inputBox, 0, 0, 2, 1);
    grid->addWidget(commandLayout, 2, 0, 1, 1);
    grid->addWidget(outputLayout, 0, 1, 3, 1);

    grid->setAlignment(Qt::AlignCenter);
    //grid->setSpacing(2);
    //grid->setHorizontalSpacing(2);



    this->setLayout(grid);
}

QGroupBox * CyclicCodesWidget::createInputLayout() {
    QGroupBox *inputGroupBox = new QGroupBox("1. Введите исходные данные");
    QFormLayout *formLayout = new QFormLayout;

    QRegExp polynomialRegExp("[01]{1,16}");
    QRegExp probabilityRegExp("0\\.\\d{0,9}");

    QLabel *informLabel = new QLabel("Информационный полином: ");
    informationPolyEdit = new QLineEdit("10010101");
    informationPolyEdit->setValidator(new QRegExpValidator(polynomialRegExp, this));

    QLabel *genLabel = new QLabel("Порождающий полином: ");
    generatorListChooser = new QComboBox();
    generatorListChooser->addItem("1101");
    generatorListChooser->addItem("1001");

    QLabel *probLabel = new QLabel("Вероятность искажения: ");
    probabilityEdit = new QLineEdit("0.0001");
    probabilityEdit->setValidator(new QRegExpValidator(probabilityRegExp, this));

    QLabel *expCountLabel = new QLabel("Количество испытаний: ");
    experimentsCountEdit = new QLineEdit("1000000");
    experimentsCountEdit->setValidator(new QIntValidator(1, 1000000000, this));

    formLayout->addRow(informLabel, informationPolyEdit);
    formLayout->addRow(genLabel, generatorListChooser);
    formLayout->addRow(probLabel, probabilityEdit);
    formLayout->addRow(expCountLabel, experimentsCountEdit);

    inputGroupBox->setLayout(formLayout);
    return inputGroupBox;
}

QGroupBox * CyclicCodesWidget::createCommandLayout() {
    QGroupBox *commandBox = new QGroupBox("2. Начать работу");
    QGridLayout *layout = new QGridLayout;

    startButton = new QPushButton("Начать");
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(onButtonClick()));
    progressBar = new QProgressBar;

    layout->addWidget(startButton, 0, 0, 1, 1);
    layout->addWidget(progressBar, 1, 0, 1, 1);

    commandBox->setLayout(layout);
    return commandBox;
}

QGroupBox * CyclicCodesWidget::createOutputLayout() {
    QGroupBox *outputBox = new QGroupBox("3. Результаты");
    QFormLayout *formLayout = new QFormLayout;

    QLabel *experimentsDoneLabel = new QLabel("Количесвто испытаний: ");
    QLabel *receivedCorrectlyLabel = new QLabel("Принято без искажений: ");
    QLabel *errorDetectedLabel = new QLabel("Обнаружено ошибок");
    QLabel *errorMissedLabel = new QLabel("Пропущено ошибок");
    experimentsDoneResult = new QLabel("0");
    receivedCorrectlyResult = new QLabel("0");
    errorDetectedResult = new QLabel("0");
    errorMissedResult = new QLabel("0");

    formLayout->addRow(experimentsDoneLabel, experimentsDoneResult);
    formLayout->addRow(receivedCorrectlyLabel, receivedCorrectlyResult);
    formLayout->addRow(errorDetectedLabel, errorDetectedResult);
    formLayout->addRow(errorMissedLabel, errorMissedResult);

    outputBox->setLayout(formLayout);
    return outputBox;
}

void CyclicCodesWidget::parseBoolVector(std::vector<bool> &output, const QString &text) {
    output.clear();
    for (int i = text.length() - 1; i >= 0; --i) {
        QChar symbol = text[i];
        if (symbol == '0') {
            output.push_back(false);
        } else if (symbol == '1') {
            output.push_back(true);
        }
    }
}

void CyclicCodesWidget::onButtonClick() {
    startButton->setEnabled(false);

    std::vector<bool> vector;
    QString informationText = informationPolyEdit->text();
    parseBoolVector(vector, informationText);

    std::vector<bool> generatorVector;
    QString generatorText = generatorListChooser->currentText();
    parseBoolVector(generatorVector, generatorText);

    int operationsCount = experimentsCountEdit->text().toInt();
    double corruptionProbability = probabilityEdit->text().toDouble();
    lab->startProcess(vector, generatorVector, operationsCount, corruptionProbability);

    progressBar->setMinimum(0);
    progressBar->setMaximum(operationsCount);
    progressBar->setValue(0);

    updateTimer->start(UPDATE_TIMER_DELAY_MILLIS);
}

void CyclicCodesWidget::onSendProcessFinished(CyclicLabResult result) {
    updateTimer->stop();
    progressBar->setValue(result.getExperimentsDone());
    startButton->setEnabled(true);

    experimentsDoneResult->setText(QString::number(result.getExperimentsDone()));
    receivedCorrectlyResult->setText(QString::number(result.getReceivedCorrectly()));
    errorDetectedResult->setText(QString::number(result.getErrorDetected()));
    errorMissedResult->setText(QString::number(result.getMissedErrors()));
}

void CyclicCodesWidget::updateResult() {
    CyclicLabResult result = lab->getResult();

    experimentsDoneResult->setText(QString::number(result.getExperimentsDone()));
    receivedCorrectlyResult->setText(QString::number(result.getReceivedCorrectly()));
    errorDetectedResult->setText(QString::number(result.getErrorDetected()));
    errorMissedResult->setText(QString::number(result.getMissedErrors()));

    progressBar->setValue(result.getExperimentsDone());
}

void CyclicCodesWidget::setInfo(std::string text) {
    QString string = QString::fromUtf8(text.c_str());
    this->setWindowTitle(string);
}
