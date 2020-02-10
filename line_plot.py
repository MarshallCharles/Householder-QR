import altair as alt
import pandas as pd
from termcolor import colored

TWOCOL = ['Size', 'Time (s)']
THREECOL = ['Size', 'Time (s)', 'label']
l = None
def lineColor(df,x,y,color):
    return alt.Chart(df,height = 550, width = 550).mark_line(point= True).encode(
                        alt.X(x),alt.Y(y),
                        alt.Color(color, type = 'nominal',scale = alt.Scale(scheme = 'category10')))\
                    .configure_legend(clipHeight = 10,\
                        titleFontSize= 17,labelFontSize = 17,symbolSize = 200,\
                        symbolStrokeWidth = 3)\
                    .configure_axis(labelFontSize=17, titleFontSize=17).interactive()
def line(df,x,y):
    return alt.Chart(df,height = 550, width = 550).mark_line(point= True).encode(
                        alt.X(x),alt.Y(y)).configure_legend(clipHeight = 10,\
                        titleFontSize= 17,labelFontSize = 17,symbolSize = 200, \
                        symbolStrokeWidth = 3)\
                    .configure_axis(labelFontSize=17, titleFontSize=17).interactive()

def handle_string(s, a):
    temp = []
    x = [x.strip() for x in s.split(',')]
    for i in range(len(x)):
        if i<2:
            temp.append(int(x[i]))
        else:
            temp.append(x[i])
    a.append(temp)
    return a

def parse():
    arr = []
    while 1:
        print(colored('Current input = {}'.format(arr),'cyan'))
        new = input(">>>")
        if new=='q': return arr
        arr = handle_string(new,arr)

def make_df(d):
    c = TWOCOL if len(d[1])<3 else THREECOL
    return pd.DataFrame(d, columns = c)

def main():
    data = parse()
    df = make_df(data)
    if len(list(df))<3:
        line(df,'Size:N','Time (s):Q').serve()
    else:
        line(df,'Size:N','Time (s):Q', 'label').serve()


if __name__=='__main__':
    main()
