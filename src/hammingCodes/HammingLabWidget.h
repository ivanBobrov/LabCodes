#ifndef HAMMING_CODES_HAMMING_LAB_WIDGET_H
#define HAMMING_CODES_HAMMING_LAB_WIDGET_H

#include <QtWidgets>
#include <vector>
#include <string>
#include "HammingLabEventEmitter.h"
#include "HammingCodesLab.h"
#include "HammingCodeLabel.h"

Q_DECLARE_METATYPE(HammingLabResult)

class HammingLabWidget : public QWidget {

Q_OBJECT

private:
    HammingCodesLab *hammingCodesLab;
    HammingLabEventEmitter* eventEmitter;

    QPushButton *buttonStart;
    QPushButton *buttonPause;
    QPushButton *buttonResume;
    QPushButton *buttonClear;
    QLineEdit *informationMessageLineEdit;
    QLineEdit *probabilityLineEdit;
    QLineEdit *attemptsCountLineEdit;
    QLabel *informationMessageDisplay;
    HammingCodeLabel *codedMessageDisplay;
    QLabel *doneAttempts;
    QLabel *rightReceived;
    QLabel *repairedCount;
    QLabel *errorMissed;
    QProgressBar *progressBar;

    void createLayouts();
    QGroupBox * createInputLayout();
    QGroupBox * createControlLayout();
    QGroupBox * createStatisticsLayout();
    QGroupBox * createConclusionLayout();
    std::string boolArrayToString(std::vector<bool> &array);
    std::vector<bool> parseInformationMessageText(const QString &text);
    void setStatusInfo(QString message);

public:
    HammingLabWidget();

signals:
    void statusInfo(QString message);

public slots:
    void onStartButtonClick();
    void onPauseButtonClick();
    void onResumeButtonClick();
    void onClearButtonClick();
    void onInformationLineEditChanged(const QString &text);
    void onProbabilityLineEditChanged();
    void onAttemptsCountLineEditChanged();

    void onStartProcess();
    void onPauseProcess();
    void onResumeProcess();
    void onSendProcessFinished(const HammingLabResult &results);
    void onInformationMessageChanged(std::vector<bool> &infoMessage, std::vector<bool> &codedMessage);
    void onProbabilityChanged(double newProbability);
    void onAttemptsCountChanged(int newAttemptsCount);
    void onResultsChanged(const HammingLabResult &results);

};

#endif //HAMMING_CODES_HAMMING_LAB_WIDGET_H