#include <QApplication>
#include <QWidget>
#include "HammingLabWidget.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);

	MainWindow mainWindow;
	mainWindow.show();

	return application.exec();
}

/*
 * TODO list:
 *
 *		1. Static linking Qt5 on Windows OS.
 *		2. Statistic's layout elements should be fit each other (by width).
 *		3. Try to replace statistics labels with lineEdits with gray background.
 *		4. Move hamming lab sources into separate folder.
 *		5. Work with thread should be done in separate class.
 *		6. Create main widget (for lab selection)
 *		7. Implement multi-threaded process.
 *		8. Icon of application
 *		9. Create cyclic codes lab widget
 *		10. Status bar has bigger font size than usual text. It shouldn't be set in points, or set in points everywhere
 *
 *	TODO: out-of-list
 *		1. Hamming codes. Decimal delimiter on input fields
 *		2. Hamming codes. Highlight check bits in coded message on the screen
 */