# -*- coding: UTF-8 -*-
from math import log

"""
函数说明:创建测试数据集

Parameters:
    无
Returns:
    dataSet - 数据集
    labels - 分类属性
Author:
    Jack Cui
"""

"""
年龄：0代表青年，1代表中年，2代表老年；
有工作：0代表否，1代表是；
有自己的房子：0代表否，1代表是；
信贷情况：0代表一般，1代表好，2代表非常好；
类别(是否给贷款)：no代表否，yes代表是。
"""

def createDataSet():
    dataSet =  [[0, 0, 0, 0, 'no'],         #数据集
            [0, 0, 0, 1, 'no'],
            [0, 1, 0, 1, 'yes'],
            [0, 1, 1, 0, 'yes'],
            [0, 0, 0, 0, 'no'],
            [1, 0, 0, 0, 'no'],
            [1, 0, 0, 1, 'no'],
            [1, 1, 1, 1, 'yes'],
            [1, 0, 1, 2, 'yes'],
            [1, 0, 1, 2, 'yes'],
            [2, 0, 1, 2, 'yes'],
            [2, 0, 1, 1, 'yes'],
            [2, 1, 0, 1, 'yes'],
            [2, 1, 0, 2, 'yes'],
            [2, 0, 0, 0, 'no']]
    labels = ['年龄', '有工作', '有自己的房子', '信贷情况']  # 分类属性
    return dataSet, labels  # 返回数据集和分类属性

"""
函数说明:计算给定数据集的经验熵(香农熵)

Parameters:
    dataSet - 数据集
Returns:
    shannonEnt - 经验熵(香农熵)
"""
def calcShannonEnt(dataSet):
    numEntrires = len(dataSet)                        #返回数据集的行数
    labelCounts = {}                                  #保存每个标签(Label)出现次数的字典
    for featVec in dataSet:                           #对每组特征向量进行统计(每列)
        currentLabel = featVec[-1]                    #提取标签(Label)信息
        if currentLabel not in labelCounts.keys():    #如果标签(Label)没有放入统计次数的字典,添加进去
            labelCounts[currentLabel] = 0
        labelCounts[currentLabel] += 1                #Label计数
    shannoEnt = 0.0                                   #经验熵(香农熵)
    for key in labelCounts:                           #计算香农熵
        prob = float(labelCounts[key])/numEntrires    #选择该标签(Label)的概率
        shannoEnt -= prob * log(prob,2)               #利用公式计算
    return shannoEnt                                  #返回经验熵(香农熵)


"""
函数说明:按照给定特征划分数据集

Parameters:
    dataSet - 待划分的数据集
    axis - 划分数据集的特征
    value - 需要返回的特征的值
Returns:
    无
"""
def splitDataSet(dataSet,axis,value):
    reDataSet = []                         #创建返回的数据集列表
    for featVec in dataSet:                 #遍历数据集
        if featVec[axis] == value:
            reducedFeatVec = featVec[:axis]   #去掉axis特征
            reducedFeatVec.extend(featVec[axis+1:])   #将符合条件的添加到返回的数据集
            reDataSet.append(reducedFeatVec)
    return reDataSet                          #返回划分后的数据集

"""
函数说明:选择最优特征

Parameters:
    dataSet - 数据集
Returns:
    bestFeature - 信息增益最大的(最优)特征的索引值
"""
def chooseBestFeatureToSplit(dataSet):
    numFeatures = len(dataSet[0])-1
    baseEntropy = calcShannonEnt(dataSet)
    bestInfoGain = 0.0
    bestFeature = -1
    for i in range(numFeatures):
        #获取dataSet的第i个所有特征
        featlist = [example[i] for example in dataSet]
        uniqueVals = set(featlist)
        newEntropy = 0.0
        for value in uniqueVals:
            subDataSet = splitDataSet(dataSet, i, value)         # subDataSet划分后的子集
            prob = len(subDataSet) / float(len(dataSet))         # 计算子集的概率
            newEntropy += prob * calcShannonEnt(subDataSet)       # 根据公式计算经验条件熵
        infoGain = baseEntropy - newEntropy                         # 信息增益
        print("第%d个特征的增益为%.3f" % (i, infoGain))          # 打印每个特征的信息增益
        if (infoGain > bestInfoGain):                            # 计算信息增益
            bestInfoGain = infoGain                              # 更新信息增益，找到最大的信息增益
            bestFeature = i                                       # 记录信息增益最大的特征的索引值
    return bestFeature

if __name__ == '__main__':
    dataSet,features = createDataSet()
    print(dataSet)
    print("香农熵为：")
    print(calcShannonEnt(dataSet))
    print("最优特征索引值:" + str(chooseBestFeatureToSplit(dataSet)))
