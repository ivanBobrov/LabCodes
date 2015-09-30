#include <QApplication>
#include <QWidget>
#include "HammingLabWidget.h"

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);

	HammingLabWidget widget;
	widget.show();

	return application.exec();
}

/*
 * TODO list:
 *
 *		1. Implement Pause button.
 *		2. Implement Clear (or "Stop" button).
 *		3. Repair hamming code-decode.
 *		4. Handle 1- and 2-length information messages.
 *		5. Status label should be in the bottom of the layout. Use QStatusBar.
 *		6. Static linking Qt5 on Windows OS.
 *		7. Statistic's layout elements should be fit each other (by width).
 *		8. Cyclic codes widget.
 *		9. Implement multi-threaded process.
 *		10. Icon of application
 *
 *	TODO: out-of-list
 *		1. Decimal delimiter on input fields
 *		2. Highlight check bits in coded message on the screen
 */