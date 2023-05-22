from os import system
from parameters import *
import wx, time, serial
import com

class MyFrame(wx.Frame):
    def __init__(self, parent, title):
        super(MyFrame, self).__init__(parent,
                                      title=title,
                                      size=(320,200),
                                      pos=(400, 300))
        self.panel = MyPanel(self)
 
class MyPanel(wx.Panel):
    def __init__(self, parent):
        super(MyPanel, self).__init__(parent)
        font0 = wx.Font(9,
                        wx.FONTFAMILY_DEFAULT,
                        wx.FONTSTYLE_NORMAL,
                        wx.FONTWEIGHT_BOLD) 
        
        label0 = wx.StaticText(self,
                               label=TEXT0,
                               style=wx.ALIGN_LEFT,
                               pos=(90, 20))
        label0.SetFont(font0)
        
        label1 = wx.StaticText(self,
                               label=TEXT1,
                               style=wx.ALIGN_LEFT|wx.TE_MULTILINE,
                               pos=(90, 40))

        wx.TE_MULTILINE
        
        self.slider = wx.Slider(self, value=50, minValue=0, maxValue=100,
                                style=wx.SL_LABELS | wx.SL_VERTICAL,
                                pos=(20, 16))


        self.timer0 = wx.Timer(self, 0)
        self.Bind(wx.EVT_TIMER, self.Send, self.timer0)
        self.timer0.Start(100)    # 100 ms
        self.counter = 0
        
    def Send(self, e):
        val = self.slider.GetValue()
        try:
            ser.write(chr(val).encode())
            self.counter += 1
            print('{:5d}'.format(self.counter), ": value =", val)
        except serial.SerialException:
            print("Connection Lost!")
            input("Press 'Enter' to exit ")
            exit()
    
class MyApp(wx.App):
    def OnInit(self):
        self.frame = MyFrame(None, TITLE)
        self.frame.Show()
        return True


serState = com.KeepAlive()

while not serState[0]:
    print("Make sure TIVA-C is connected!")
    input("Press 'Enter' to try again ")
    serState = com.KeepAlive()
    print()
else:
    system('cls')
    print("Connected to TIVA-C device through %s"%(serState[1]))
    print("Sending slider value through UART every 100 ms\n")
    ser = com.StartCom(serState[1])
    app = MyApp()
    app.MainLoop()
 


