# -*- coding: utf-8 -*-

try:
    from PySide import QtCore
except:
    from PyQt4.QtCore import pyqtSlot as Slot
    from PyQt4 import QtCore
    from panda3d import windoeFramework


class pyform(QtCore.QObject):
    def __init__(self):
        QtCore.QObject.__init__(self)
        pass
