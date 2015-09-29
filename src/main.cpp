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
 *		1. Explicit work steps should be on the screen.
 *		2. Structure of layouts should also be in order of work steps.
 *		3. Implement Pause button.
 *		4. Implement Clear (or "Stop" button).
 *		5. Repair hamming code-decode.
 *		6. Handle 1- and 2-length information messages.
 *		7. Status label should be in the bottom of the layout.
 *		8. Static linking Qt5 on Windows OS.
 *		9. Implement multi-threaded process.
 *		10. Statistic's layout elements should be fit each other (by width).
 *		11. Cyclic codes widget.
 *		12. Icon of application
 *
 *	TODO: out-of-list
 *		1. Decimal delimiter on input fields
 *		2. Highlight check bits in coded message on the screen
 */