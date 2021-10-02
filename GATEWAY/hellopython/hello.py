from tkinter import *
import tkinter

window = Tk()
window.title("Hello tkinter")
window.geometry("400x200")

# lable
lab = Label(window, text="Xin chào Hoàng Lê", fg='red',font=("Arial",14))
lab_2 = Label(window, text="Đói bụng rồi", fg='blue',font=("Arial",14))
lab.grid(column=0,row=0)
lab_2.grid(column=0,row=1)

# textbox
text_in = Entry(window, width=20)
text_in.grid(column=1, row=0)

# butt
butt = Button(window, width=10, height=2, text= "okay")
butt.grid(column=1, row=1)
window.mainloop()



