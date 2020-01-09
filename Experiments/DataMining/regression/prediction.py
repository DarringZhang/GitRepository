# encoding=utf-8
#开始建立模型进行预测

import xlrd
import xlwt
import pandas as pd
import numpy as np
import tensorflow as tf
inputfile='data4.csv'
data= pd.read_csv(inputfile)

# from sklearn.linear_model import Lasso
# # LASSO回归的特点是在拟合广义线性模型的同时进行变量筛选和复杂度调整。 因此，不论目标因变量是连续的，还是二元或者多元离散的，
# #都可以用LASSO回归建模然后预测。 这里的变量筛选是指不把所有的变量都放入模型中进行拟合，而是有选择的把变量放入模型从而得到更好的性能参数。
# model = Lasso()
# model.fit(data.iloc[:,0:13], data['y'])
# q=model.coef_   #各特征的系数
# q=pd.DataFrame(q,index=['x1','x2','x3','x4','x5','x6','x7','x8','x9','x10','x11','x12','x13']).T
# np.round(q,4).to_csv('dataLasso.csv')
# #得出 可以踢掉x12


#分析Pearson相关系数，可以得出，踢掉X11



#地方财政收入神经网络预测模型
inputfile='data.csv'
outputfile='revenue.xls'
modelfile='1-net.model'
data=pd.read_csv(inputfile)
print(data)
feature=['x1','x2','x3','x4','x5','x6','x7','x8','x9','x10','x12','x13']#特征所在列
data_train=data.loc[range(0,19)].copy() #取2015年前的建模数据
data_mean=data_train.mean()
data_std=data_train.std()
data_train=(data_train-data_mean)/data_std#数据标准化
x_train=data_train[feature].as_matrix()#特征数据
y_train=data_train['y'].as_matrix()#标签数据
from keras.models import Sequential
from keras.layers.core import Dense,Activation

tf.reset_default_graph()
model=Sequential()#建立模型
model.add(Dense(input_dim=12,output_dim=12))
model.add(Activation('relu'))#激活函数
model.add(Dense(input_dim=12,output_dim=1))
model.compile(loss='mean_squared_error',optimizer='adam')#编译模型，目标函数是均方差
model.fit(x_train,y_train,nb_epoch=10000,batch_size=2)#训练模型
model.save_weights(modelfile)#保存模型
#预测并还原结果
x=((data[feature]-data_mean[feature])/data_std[feature]).as_matrix()
data[u'y_pred'] = model.predict(x) * data_std['y'] + data_mean['y']
data.to_excel(outputfile)
#画出预测图
import matplotlib.pyplot as plt
p=data[['y','y_pred']].plot(subplots=True,style=['b-o','r-*'])
plt.show()


