#include "HammingLabWidget.h"

HammingLabWidget::HammingLabWidget() {
    createLayouts();

    eventEmitter = new HammingLabEventEmitter; //TODO: destructor
    qRegisterMetaType<HammingLabResult>("HammingLabResult");
    QObject::connect(eventEmitter, SIGNAL(startProcessSignal()), this, SLOT(onStartProcess()));
    QObject::connect(eventEmitter, SIGNAL(pauseProcessSignal()), this, SLOT(onPauseProcess()));
    QObject::connect(eventEmitter, SIGNAL(resumeProcessSignal()), this, SLOT(onResumeProcess()));
    QObject::connect(eventEmitter, SIGNAL(informationMessageChangedSignal(std::vector<bool>&, std::vector<bool>&)),
                     this, SLOT(onInformationMessageChanged(std::vector<bool>&, std::vector<bool>&)));
    QObject::connect(eventEmitter, SIGNAL(probabilityChangedSignal(double)), this, SLOT(onProbabilityChanged(double)));
    QObject::connect(eventEmitter, SIGNAL(attemptsCountChangedSignal(int)), this, SLOT(onAttemptsCountChanged(int)));
    QObject::connect(eventEmitter, SIGNAL(resultsChangedSignal(const HammingLabResult&)),
                     this, SLOT(onResultsChanged(const HammingLabResult&)));
    QObject::connect(eventEmitter, SIGNAL(sendProcessFinishedSignal(const HammingLabResult&)),
                     this, SLOT(onSendProcessFinished(const HammingLabResult&)));

    hammingCodesLab = HammingCodesLab::createInstance(eventEmitter);
    setStatusInfo("Ready");
}

void HammingLabWidget::onStartProcess() {
    buttonStart->setEnabled(false);
    buttonPause->setEnabled(true);
    buttonClear->setEnabled(true);
    informationMessageLineEdit->setEnabled(false);
    probabilityLineEdit->setEnabled(false);
    attemptsCountLineEdit->setEnabled(false);

    setStatusInfo("Send process started");
}

void HammingLabWidget::onPauseProcess() {
    buttonPause->setEnabled(false);
    buttonResume->setEnabled(true);
    setStatusInfo("Send process paused");
}

void HammingLabWidget::onResumeProcess() {
    buttonResume->setEnabled(false);
    buttonPause->setEnabled(true);
    setStatusInfo("Send process resumed");
}

void HammingLabWidget::onSendProcessFinished(const HammingLabResult &results) {
    progressBar->setEnabled(false);

    informationMessageLineEdit->setEnabled(true);
    probabilityLineEdit->setEnabled(true);
    attemptsCountLineEdit->setEnabled(true);

    buttonStart->setEnabled(true);
    buttonPause->setEnabled(false);
    buttonResume->setEnabled(false);
    buttonClear->setEnabled(false);
    setStatusInfo("Send process successfully done");
}

void HammingLabWidget::onInformationMessageChanged(std::vector<bool> &infoMessage, std::vector<bool> &codedMessage) {
    QString infoString = QString::fromStdString(boolArrayToString(infoMessage));
    QString codedString = QString::fromStdString(boolArrayToString(codedMessage));

    if (!infoString.isEmpty()) {
        informationMessageDisplay->setStyleSheet("");
        informationMessageDisplay->setText(infoString);
        codedMessageDisplay->setText(codedString);

        setStatusInfo("Information message changed: " + infoString);
    } else {
        informationMessageDisplay->setStyleSheet("color: lightgrey");
        informationMessageDisplay->setText("insert message polynomial");
        codedMessageDisplay->setText("");

        setStatusInfo("Information message cleared");
    }

}

void HammingLabWidget::onProbabilityChanged(double newProbability) {
    setStatusInfo("Probability changed: " + QString::number(newProbability));
}

void HammingLabWidget::onAttemptsCountChanged(int newAttemptsCount) {
    setStatusInfo("Attempts count changed: " + QString::number(newAttemptsCount));
}

void HammingLabWidget::onResultsChanged(const HammingLabResult &results) {
    progressBar->setMinimum(0);
    progressBar->setMaximum(results.getAttemptCount());
    progressBar->setValue(results.getDoneAttemptCount());

    doneAttempts->setText(QString::number(results.getDoneAttemptCount()));
    rightReceived->setText(QString::number(results.getSuccessfullyReceivedCount()));
    repairedCount->setText(QString::number(results.getRepairedCount()));
    errorMissed->setText(QString::number(results.getErrorMissedCount()));
}

void HammingLabWidget::onStartButtonClick() {
    hammingCodesLab->startSendProcess();
}

void HammingLabWidget::onPauseButtonClick() {
    hammingCodesLab->pauseSendProcess();
}

void HammingLabWidget::onResumeButtonClick() {
    hammingCodesLab->resumeSendProcess();
}

void HammingLabWidget::onClearButtonClick() {
    hammingCodesLab->stopSendProcess();
}

void HammingLabWidget::onInformationLineEditChanged(const QString &text) {
    std::vector<bool> vector = parseInformationMessageText(text);
    hammingCodesLab->setInformationMessage(vector);
}

void HammingLabWidget::onProbabilityLineEditChanged() {
    QString string = probabilityLineEdit->text();
    double probability = string.toDouble();
    hammingCodesLab->setProbability(probability);
}


void HammingLabWidget::onAttemptsCountLineEditChanged() {
    QString string = attemptsCountLineEdit->text();
    int attemptsCount = string.toInt();
    hammingCodesLab->setAttemptsCount(attemptsCount);
}

void HammingLabWidget::createLayouts() {
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(createInputLayout(), 0, 0, 1, 1);
    mainLayout->addWidget(createControlLayout(), 1, 0, 1, 1);
    mainLayout->addWidget(createStatisticsLayout(), 2, 0, 1, 1);
    mainLayout->addWidget(createConclusionLayout(), 3, 0, 1, 1);

    //mainLayout->setRowStretch(4, 1);

    this->setLayout(mainLayout);
}

QGroupBox * HammingLabWidget::createInputLayout() {
    // Group box and layout for input text edits
    QGroupBox *inputGroupBox = new QGroupBox("1. Введите исходные данные");
    QFormLayout *inputLayout = new QFormLayout;

    //Creating line edits for layout TODO: what's about freeing memory of validators? Or any other created object?
    informationMessageLineEdit = new QLineEdit("10101");
    probabilityLineEdit = new QLineEdit("0.0001");
    attemptsCountLineEdit = new QLineEdit("5000000");

    QRegExp informationLineEditRegExp("[01]{1,16}");
    QRegExp probabilityLineEditRegExp("0\\.\\d{0,9}");

    informationMessageLineEdit->setValidator(new QRegExpValidator(informationLineEditRegExp, this));
    probabilityLineEdit->setValidator(new QRegExpValidator(probabilityLineEditRegExp, this));
    attemptsCountLineEdit->setValidator(new QIntValidator(1, 1000000000, this));

    //Connecting line edits signals with slots
    QObject::connect(informationMessageLineEdit, SIGNAL(textChanged(QString)),
                     this, SLOT(onInformationLineEditChanged(QString)));
    QObject::connect(probabilityLineEdit, SIGNAL(editingFinished()),
                     this, SLOT(onProbabilityLineEditChanged()));
    QObject::connect(attemptsCountLineEdit, SIGNAL(editingFinished()),
                     this, SLOT(onAttemptsCountLineEditChanged()));

    //Adding line edits to layout
    inputLayout->addRow("Информационное сообщение", informationMessageLineEdit);
    inputLayout->addRow("Вероятность искажения элемента", probabilityLineEdit);
    inputLayout->addRow("Количество передач информации", attemptsCountLineEdit);

    //Set layout to group box
    inputGroupBox->setLayout(inputLayout);
    inputGroupBox->setMinimumSize(430, 125);
    inputGroupBox->setMaximumSize(700, 180);

    return inputGroupBox;
}

QGroupBox * HammingLabWidget::createControlLayout() {
    //Create group box and layout for control buttons
    QGroupBox *controlGroupBox = new QGroupBox("2. Начать работу");
    QVBoxLayout *controlLayout = new QVBoxLayout;

    //Layout for button
    QHBoxLayout *controlButtonLayout = new QHBoxLayout;

    //Creating buttons
    buttonStart = new QPushButton("Начать");
    buttonPause = new QPushButton("Приостановить"); buttonPause->setEnabled(false);
    buttonResume = new QPushButton("Продолжить"); buttonResume->setEnabled(false);
    buttonClear = new QPushButton("Сбросить"); buttonClear->setEnabled(false);
    QObject::connect(buttonStart, SIGNAL(clicked()), this, SLOT(onStartButtonClick()));
    QObject::connect(buttonPause, SIGNAL(clicked()), this, SLOT(onPauseButtonClick()));
    QObject::connect(buttonResume, SIGNAL(clicked()), this, SLOT(onResumeButtonClick()));
    QObject::connect(buttonClear, SIGNAL(clicked()), this, SLOT(onClearButtonClick()));
    controlButtonLayout->addWidget(buttonStart);
    controlButtonLayout->addWidget(buttonPause);
    controlButtonLayout->addWidget(buttonResume);
    controlButtonLayout->addWidget(buttonClear);

    //Set button layout to be in a control layout
    controlLayout->addLayout(controlButtonLayout);

    //Adding progress bar to layout
    progressBar = new QProgressBar;
    controlLayout->addWidget(progressBar);

    //Applying layout to group box
    controlGroupBox->setLayout(controlLayout);
    controlGroupBox->setMinimumSize(250, 100);
    controlGroupBox->setMaximumSize(700, 150);

    return controlGroupBox;
}


QGroupBox * HammingLabWidget::createStatisticsLayout() {
    QFont bigFont("Arial", 18);
    QGroupBox *statisticsGroupBox = new QGroupBox("3. Результаты");

    QFormLayout *statisticsLayout = new QFormLayout;

    informationMessageDisplay = new QLabel();
    informationMessageDisplay->setFont(bigFont);
    codedMessageDisplay = new QLabel();
    codedMessageDisplay->setFont(bigFont);
    doneAttempts = new QLabel("0");
    rightReceived = new QLabel("0");
    repairedCount = new QLabel("0");
    errorMissed = new QLabel("0");


    statisticsLayout->addRow("Информационное сообщение: ", informationMessageDisplay);
    statisticsLayout->addRow("Передаваемое сообщение: ", codedMessageDisplay);
    statisticsLayout->addRow("Количество проведённых опытов: ", doneAttempts);
    statisticsLayout->addRow("Переданные без искажения сообщения: ", rightReceived);
    statisticsLayout->addRow("Исправленные сообщения: ", repairedCount);
    statisticsLayout->addRow("Сообщения с необнаруженными искаженими:", errorMissed);

    statisticsGroupBox->setLayout(statisticsLayout);
    statisticsGroupBox->setMinimumSize(600, 200);
    statisticsGroupBox->setMaximumWidth(700);

    return statisticsGroupBox;
}

QGroupBox * HammingLabWidget::createConclusionLayout() {
    return new QGroupBox("4. Сделайте выводы");
}

std::string HammingLabWidget::boolArrayToString(std::vector<bool> &array) {
    std::string result;
    for (std::vector<bool>::reverse_iterator it = array.rbegin(); it < array.rend(); it++) {
        result.append(*it ? "1" : "0");
    }

    return result;
}

std::vector<bool> HammingLabWidget::parseInformationMessageText(const QString &text) {
    std::vector<bool> result;
    for (int i = text.length() - 1; i >= 0; i--) {
        QChar symbol = text[i];
        if (symbol == '0') {
            result.push_back(false);
        } else if (symbol == '1') {
            result.push_back(true);
        }
    }

    return result;
}

void HammingLabWidget::setStatusInfo(QString message) {
    emit statusInfo(message);
}
