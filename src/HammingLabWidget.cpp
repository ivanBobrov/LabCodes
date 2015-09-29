#include "HammingLabWidget.h"

HammingLabWidget::HammingLabWidget() {
    createLayouts();
    eventEmitter = new HammingLabEventEmitter; //TODO: destructor
    qRegisterMetaType<HammingLabResult>("HammingLabResult");
    QObject::connect(eventEmitter, SIGNAL(startProcessSignal()), this, SLOT(onStartProcess()));
    QObject::connect(eventEmitter, SIGNAL(pauseProcessSignal()), this, SLOT(onPauseProcess()));
    QObject::connect(eventEmitter, SIGNAL(informationMessageChangedSignal(std::vector<bool>&, std::vector<bool>&)),
                     this, SLOT(onInformationMessageChanged(std::vector<bool>&, std::vector<bool>&)));
    QObject::connect(eventEmitter, SIGNAL(probabilityChangedSignal(double)), this, SLOT(onProbabilityChanged(double)));
    QObject::connect(eventEmitter, SIGNAL(attemptsCountChangedSignal(int)), this, SLOT(onAttemptsCountChanged(int)));
    QObject::connect(eventEmitter, SIGNAL(resultsChangedSignal(const HammingLabResult&)),
                     this, SLOT(onResultsChanged(const HammingLabResult&)));
    QObject::connect(eventEmitter, SIGNAL(sendProcessFinishedSignal(const HammingLabResult&)),
                     this, SLOT(onSendProcessFinished(const HammingLabResult&)));

    hammingCodesLab = HammingCodesLab::createInstance(eventEmitter);
}

void HammingLabWidget::onStartProcess() {
    buttonStart->setEnabled(false);
    informationMessageLineEdit->setEnabled(false);
    probabilityLineEdit->setEnabled(false);
    attemptsCountLineEdit->setEnabled(false);

    statusLabel->setText("Send process started");
}

void HammingLabWidget::onPauseProcess() {

}

void HammingLabWidget::onInformationMessageChanged(std::vector<bool> &infoMessage, std::vector<bool> &codedMessage) {
    QString string = QString::fromStdString(boolArrayToString(infoMessage));
    QString coded = QString::fromStdString(boolArrayToString(codedMessage));

    if (!string.isEmpty()) {
        informationMessageDisplay->setStyleSheet("");
        informationMessageDisplay->setText(string);
        codedMessageDisplay->setText(coded);

        statusLabel->setText("Information message changed: " + string);
    } else {
        informationMessageDisplay->setStyleSheet("color: lightgrey");
        informationMessageDisplay->setText("insert message polynomial");
        codedMessageDisplay->setText("");

        statusLabel->setText("Information message cleared");
    }

}

void HammingLabWidget::onProbabilityChanged(double newProbability) {
    statusLabel->setText("Probability changed: " + QString::number(newProbability));
}

void HammingLabWidget::onAttemptsCountChanged(int newAttemptsCount) {
    statusLabel->setText("Attempts count changed: " + QString::number(newAttemptsCount));
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

void HammingLabWidget::onSendProcessFinished(const HammingLabResult &results) {
    progressBar->setEnabled(false);
    statusLabel->setText("Send process successfully done");
    informationMessageLineEdit->setEnabled(true);
    probabilityLineEdit->setEnabled(true);
    attemptsCountLineEdit->setEnabled(true);
    buttonStart->setEnabled(true);
}

void HammingLabWidget::onStartButtonClick() {
    hammingCodesLab->startSendProcess();
}

void HammingLabWidget::onPauseButtonClick() {
    hammingCodesLab->pauseSendProcess();
}

void HammingLabWidget::onClearButtonClick() {
    //TODO: implement clear button handler

    std::vector<bool> vect = {false, true, true};
    hammingCodesLab->setInformationMessage(vect);
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
    QHBoxLayout *mainLayout = new QHBoxLayout;

    createControlLayout(mainLayout);
    createStatisticsLayout(mainLayout);

    this->setLayout(mainLayout);
}

void HammingLabWidget::createControlLayout(QLayout *mainLayout) {
    //TODO: docs
    QGroupBox *controlGroupBox = new QGroupBox("Исходные данные");
    QVBoxLayout *controlLayout = new QVBoxLayout;


    QFormLayout *inputParametersLayout = new QFormLayout;
    informationMessageLineEdit = new QLineEdit("10101");
    QRegExp informRegExp("[01]{1,16}");
    informationMessageLineEdit->setValidator(new QRegExpValidator(informRegExp));
    probabilityLineEdit = new QLineEdit("0.0001");
    QRegExp probabilityRegExp("0\\.\\d{0,9}");
    probabilityLineEdit->setValidator(new QRegExpValidator(probabilityRegExp));
    attemptsCountLineEdit = new QLineEdit("5000000");
    attemptsCountLineEdit->setValidator(new QIntValidator(1, 1000000000, this));

    QObject::connect(informationMessageLineEdit, SIGNAL(textChanged(QString)),
                     this, SLOT(onInformationLineEditChanged(QString)));
    QObject::connect(probabilityLineEdit, SIGNAL(editingFinished()),
                     this, SLOT(onProbabilityLineEditChanged()));
    QObject::connect(attemptsCountLineEdit, SIGNAL(editingFinished()),
                     this, SLOT(onAttemptsCountLineEditChanged()));

    inputParametersLayout->addRow("Информационное сообщение", informationMessageLineEdit);
    inputParametersLayout->addRow("Вероятность искажения элемента", probabilityLineEdit);
    inputParametersLayout->addRow("Количество передач информации", attemptsCountLineEdit);

    controlLayout->addLayout(inputParametersLayout);


    QHBoxLayout *controlButtonLayout = new QHBoxLayout;
    buttonStart = new QPushButton("Начать");
    buttonPause = new QPushButton("Pause"); buttonPause->setEnabled(false);
    buttonClear = new QPushButton("Clear"); buttonClear->setEnabled(false);
    QObject::connect(buttonStart, SIGNAL(clicked()), this, SLOT(onStartButtonClick()));
    QObject::connect(buttonPause, SIGNAL(clicked()), this, SLOT(onPauseButtonClick()));
    QObject::connect(buttonClear, SIGNAL(clicked()), this, SLOT(onClearButtonClick()));
    controlButtonLayout->addWidget(buttonStart);
    controlButtonLayout->addWidget(buttonPause);
    controlButtonLayout->addWidget(buttonClear);

    controlLayout->addLayout(controlButtonLayout);


    progressBar = new QProgressBar;
    controlLayout->addWidget(progressBar);

    controlGroupBox->setLayout(controlLayout);
    controlGroupBox->setMinimumWidth(350);
    controlGroupBox->setMaximumSize(450, 225);

    mainLayout->addWidget(controlGroupBox);
}


void HammingLabWidget::createStatisticsLayout(QLayout *mainLayout) {
    QFont bigFont("Arial", 18);
    QGroupBox *statisticsGroupBox = new QGroupBox("Результаты");

    QFormLayout *statisticsLayout = new QFormLayout;

    informationMessageDisplay = new QLabel();
    informationMessageDisplay->setFont(bigFont);
    codedMessageDisplay = new QLabel();
    codedMessageDisplay->setFont(bigFont);
    doneAttempts = new QLabel("0");
    rightReceived = new QLabel("0");
    repairedCount = new QLabel("0");
    errorMissed = new QLabel("0");
    statusLabel = new QLabel("Status label");

    statisticsLayout->addRow("Информационное сообщение: ", informationMessageDisplay);
    statisticsLayout->addRow("Передаваемое сообщение: ", codedMessageDisplay);
    statisticsLayout->addRow("Количество проведённых опытов: ", doneAttempts);
    statisticsLayout->addRow("Переданные без искажения сообщения: ", rightReceived);
    statisticsLayout->addRow("Исправленные сообщения: ", repairedCount);
    statisticsLayout->addRow("Сообщения с необнаруженными искаженими:", errorMissed);
    statisticsLayout->addWidget(statusLabel);

    statisticsGroupBox->setLayout(statisticsLayout);
    statisticsGroupBox->setMinimumWidth(450);
    statisticsGroupBox->setMaximumSize(600, 225);

    mainLayout->addWidget(statisticsGroupBox);
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
    for (int i = 0; i < text.length(); i++) {
        QChar symbol = text[i];
        if (symbol == '0') {
            result.push_back(false);
        } else if (symbol == '1') {
            result.push_back(true);
        }
    }

    return result;
}
