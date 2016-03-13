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

    QLayout *inputLayout = createInputLayout();
    QLayout *commandLayout = createCommandLayout();
    QLayout *outputLayout = createOutputLayout();
    QLayout *progressBarLayout = createProgressBarLayout();

    grid->addLayout(inputLayout, 0, 0, 2, 1);
    grid->addLayout(commandLayout, 2, 0, 1, 1);
    grid->addLayout(progressBarLayout, 3, 0, 1, 1);
    grid->addLayout(outputLayout, 0, 1, 4, 1);

    this->setLayout(grid);
}

QLayout* CyclicCodesWidget::createInputLayout() {
    QFormLayout *formLayout = new QFormLayout;

    QLabel *informLabel = new QLabel("Информационный полином: ");
    QLineEdit *informEdit = new QLineEdit;
    QLabel *genLabel = new QLabel("Порождающий полином: ");
    QLineEdit *genEdit = new QLineEdit;
    QLabel *probLabel = new QLabel("Вероятность искажения: ");
    QLineEdit *probEdit = new QLineEdit;
    QLabel *expCountLabel = new QLabel("Количество экспериментов: ");
    QLineEdit *expCountEdit = new QLineEdit;

    formLayout->addRow(informLabel, informEdit);
    formLayout->addRow(genLabel, genEdit);
    formLayout->addRow(probLabel, probEdit);
    formLayout->addRow(expCountLabel, expCountEdit);

    return formLayout;
}

QLayout *CyclicCodesWidget::createCommandLayout() {
    QHBoxLayout *layout = new QHBoxLayout;

    startButton = new QPushButton("Начать");
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(onButtonClick()));

    layout->addWidget(startButton);

    return layout;
}

QLayout *CyclicCodesWidget::createOutputLayout() {
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

    return formLayout;
}

QLayout *CyclicCodesWidget::createProgressBarLayout() {
    QHBoxLayout *layout = new QHBoxLayout;
    progressBar = new QProgressBar;
    layout->addWidget(progressBar);

    return layout;
}

void CyclicCodesWidget::onButtonClick() {
    startButton->setEnabled(false);

    std::vector<bool> vector;
    vector.push_back(true);
    vector.push_back(false);
    vector.push_back(true);
    vector.push_back(false);
    vector.push_back(false);
    vector.push_back(true);
    vector.push_back(true);

    std::vector<bool> gen;
    gen.push_back(true);
    gen.push_back(true);

    int operationsCount = 1000000;
    lab->startProcess(vector, gen, operationsCount, 0.0001);

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
}
