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
 *		1. Repair hamming code-decode.
 *		2. Handle 1- and 2-length information messages.
 *		3. Status label should be in the bottom of the layout. Use QStatusBar.
 *		4. Static linking Qt5 on Windows OS.
 *		5. Statistic's layout elements should be fit each other (by width).
 *		6. Try to replace statistics labels with lineEdits with gray background.
 *		7. Move hamming lab sources into separate folder.
 *		8. Work with thread should be done in separate class.
 *		9. Create main widget (for lab selection)
 *		10. Implement multi-threaded process.
 *		11. Icon of application
 *		12. Create cyclic codes lab widget
 *
 *	TODO: out-of-list
 *		1. Hamming codes. Decimal delimiter on input fields
 *		2. Hamming codes. Highlight check bits in coded message on the screen
 */