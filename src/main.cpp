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
 *		1. Status label should be in the bottom of the layout. Use QStatusBar.
 *		2. Static linking Qt5 on Windows OS.
 *		3. Statistic's layout elements should be fit each other (by width).
 *		4. Try to replace statistics labels with lineEdits with gray background.
 *		5. Move hamming lab sources into separate folder.
 *		6. Work with thread should be done in separate class.
 *		7. Create main widget (for lab selection)
 *		8. Implement multi-threaded process.
 *		9. Icon of application
 *		10. Create cyclic codes lab widget
 *
 *	TODO: out-of-list
 *		1. Hamming codes. Decimal delimiter on input fields
 *		2. Hamming codes. Highlight check bits in coded message on the screen
 */