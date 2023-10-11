import PySide6
import sys
from PySide6 import QtCore, QtWidgets, QtGui


class HelloWorld(QtWidgets.QWidget):
    def __init__(self) -> None:
        super().__init__()

        self.text = QtWidgets.QLabel("Hello World", alignment=QtCore.Qt.AlignCenter)

        self.layout = QtWidgets.QVBoxLayout(self)
        self.layout.addWidget(self.text)


def main() -> None:
    print("PySide6 version:", PySide6.__version__)
    app = QtWidgets.QApplication([])

    widget = HelloWorld()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec())
    pass


if __name__ == "__main__":
    main()
