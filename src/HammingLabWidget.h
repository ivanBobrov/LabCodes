#ifndef HAMMING_CODES_HAMMING_LAB_WIDGET_H
#define HAMMING_CODES_HAMMING_LAB_WIDGET_H

#include <QtWidgets>
#include <vector>
#include <string>
#include "HammingLabEventEmitter.h"
#include "HammingCodesLab.h"

Q_DECLARE_METATYPE(HammingLabResult)

class HammingLabWidget : public QWidget {

Q_OBJECT

private:
    HammingCodesLab *hammingCodesLab;
    HammingLabEventEmitter* eventEmitter;

    QPushButton *buttonStart;
    QPushButton *buttonPause;
    QPushButton *buttonClear;
    QLineEdit *informationMessageLineEdit;
    QLineEdit *probabilityLineEdit;
    QLineEdit *attemptsCountLineEdit;
    QLabel *informationMessageDisplay;
    QLabel *codedMessageDisplay;
    QLabel *doneAttempts;
    QLabel *rightReceived;
    QLabel *repairedCount;
    QLabel *errorMissed;
    QLabel *statusLabel;
    QProgressBar *progressBar;

    void createLayouts();
    void createControlLayout(QLayout *mainLayout);
    void createStatisticsLayout(QLayout *mainLayout);
    std::string boolArrayToString(std::vector<bool> &array);
    std::vector<bool> parseInformationMessageText(const QString &text);

public:
    HammingLabWidget();

public slots:
    void onStartButtonClick();
    void onPauseButtonClick();
    void onClearButtonClick();
    void onInformationLineEditChanged(const QString &text);
    void onProbabilityLineEditChanged();
    void onAttemptsCountLineEditChanged();

    void onStartProcess();
    void onPauseProcess();
    void onInformationMessageChanged(std::vector<bool> &infoMessage, std::vector<bool> &codedMessage);
    void onProbabilityChanged(double newProbability);
    void onAttemptsCountChanged(int newAttemptsCount);
    void onResultsChanged(const HammingLabResult &results);
    void onSendProcessFinished(const HammingLabResult &results);

};

#endif //HAMMING_CODES_HAMMING_LAB_WIDGET_H