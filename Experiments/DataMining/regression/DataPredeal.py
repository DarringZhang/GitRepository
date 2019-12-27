# encoding=utf-8
#描述性分析数据特点

#data4.csv 仅包含2014年之前的数据（1~18行数据），2015这一年要预测的数据不包含在内（第19行）
#预测结果：revenue.xls

import pandas as pd
import numpy as np

inputfile='data4.csv'
outputfile='analyse.csv'
data=pd.read_csv(inputfile)
r=[data.min(),data.max(),data.mean(),data.std()]#依次计算最小值、最大值、均值、标准差
r=pd.DataFrame(r,index=['MIN','MAX','MEAN', 'STD']).T
np.round(r,2).to_csv(outputfile)#保留2位小数,并输出


np.round(data.corr(method='pearson'),2).to_csv('pearson.csv')
#标准化处理
# dataNM=(data-data.min())/(data.max()-data.min())
# dataNM.to_csv('dataNM.csv')

#-*- coding: utf-8 -*-
#标准化处理,  绘图直观分析
from matplotlib import pyplot as plt
plt.rcParams['font.sans-serif']=['SimHei'] #用来正常显示中文标签
plt.rcParams['axes.unicode_minus']=False #用来正常显示负号
inputfile = 'data4.csv' #输入的数据文件
data = pd.read_csv(inputfile) #读取数据
dataNM=(data-data.min())/(data.max()-data.min())
dataNM.plot()
plt.show()

#从图中可以看出x11总体呈下降趋势，与y呈负相关关系，而其他因变量都与y呈正相关关系。