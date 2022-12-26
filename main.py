from PyQt5 import QtWidgets, uic
import sys
import subprocess


class Ui(QtWidgets.QMainWindow):
    def __init__(self):
        super(Ui, self).__init__()
        self.flag = 0
        self.text = ""
        uic.loadUi('ui.ui', self)
        self.radioButton.clicked.connect(self.changed)
        self.lineEdit.textChanged.connect(self.changed_text)
        self.pushButton.clicked.connect(self.click)
        self.show()

    def changed(self):
        if self.flag:
            self.flag = 0
        else:
            self.flag = 1

    def changed_text(self):
        self.text = self.lineEdit.text()
        self.pushButton.setEnabled(True)

    def click(self):
        self.pushButton.setEnabled(False)
        file = open("temp.txt", "w")
        file.write(self.text + "\n")
        file.write(str(self.flag))
        file.close()
        subprocess.run(["test.exe"])


app = QtWidgets.QApplication(sys.argv)
window = Ui()
app.exec_()
