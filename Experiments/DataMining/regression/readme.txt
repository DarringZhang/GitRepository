下面对各个文件进行介绍：
data.csv：  测试集
data4.csv:  训练集
DataPredeal.py ： 对数据进行描述型分析，分析输出自变量的最值，均值和方差（analyse.csv）
				 变量之间的相关性Pearson系数矩阵（pearson.csv）

prediction.py ：通过LASSO回归建模，数据预处理，选取相关性高的因素（dataLasso.csv）
		神经网络预测训练模型并进行预测处结果（revenue.xls）

GM11:	灰色预测通过鉴别系统因素之间发展趋势的相异程度，即进行关联分析，
	并对原始数据进行生成处理来寻找系统变动的规律，
	生成有较强规律性的数据序列，然后建立相应的微分方程模型，从而预测事物未来发展趋势的状况
	这里用来预测下一年的自变量x,  题目没有涉及，暂且没用到

参考文献：代码和思想  https://blog.csdn.net/y1535766478/article/details/77992544
	绘图：https://blog.csdn.net/sinat_17588957/article/details/90600420
	灰色预测：https://blog.csdn.net/u012063773/article/details/79324324
	