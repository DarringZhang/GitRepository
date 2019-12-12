# -*- coding:UTF-8 -*-
from sklearn.neural_network import MLPClassifier  # 多层神经网络分类器
from sklearn.model_selection import train_test_split
import numpy as np
import pandas as pd

# 读测试集和训练集
train_data = pd.read_csv('first_round_training_data.csv')
test_data = pd.read_csv('first_round_testing_data.csv')
# 处理数据，建立数组矩阵，防止格式变化
train_x = np.zeros([6000, 10], dtype=np.float32)
train_y = np.zeros([6000], dtype=np.int32)
# group索引
test_id = np.zeros([6000], dtype=np.int32)
test_x = np.zeros([6000, 10], dtype=np.float32)
# 字典表示
cls2int = {"Excellent": 0, "Good": 1, "Pass": 2, "Fail": 3}
for i in range(1, 11):
    par = "Parameter" + str(i)
    tmp = train_data[par]
    for j in range(6000):
        train_x[j, i - 1] = tmp[j]
        cls = cls2int[train_data["Quality_label"][j]]
        train_y[j] = cls
for i in range(1, 11):
    par = "Parameter" + str(i)
    tmp = test_data[par]
    for j in range(6000):
        test_x[j, i - 1] = tmp[j]
        ID = int(test_data["Group"][j])
        test_id[j] = ID
# print(test_x)
yes = 0


# 字符串匹配函数，对比训练集原y与训练模型再次训练出来的y是否相等
# 用于计算准确率
def com(a, b):
    if a == b:
        #print('yes')
        global yes
        yes = yes + 1
    # else:
        # print('no')
    return yes


x_train, x_test, y_train, y_test = train_test_split(train_x, train_y, test_size=0.3)
# 调用多层神经网络模型
mlp = MLPClassifier(hidden_layer_sizes=(60, 60), activation='logistic', solver='sgd', alpha=0.0001, max_iter=10000)
mlp = mlp.fit(x_train, y_train)
y = mlp.predict(x_test)
print(len(y))
print(len(y_test))
for i in range(len(y)):
    # print(y[i], y_test[i])
    yes = com(y[i], np.array(y_test[i]))
print("正确率为:", yes / 1800)
ans = mlp.predict(test_x)

f = open("ans-neuralent_test.csv", "w+")
tmp = np.zeros([120, 4])
cnt = np.zeros([120])
for i in range(6000):
    ID = test_id[i]
    tmp[ID, ans[i]] += 1
    cnt[ID] += 1
for i in range(120):
    SUM = np.sum(tmp[i, :])
    tmp[i, :] /= SUM

f.write("Group,Excellent ratio,Good ratio,Pass ratio,Fail ratio\n")
for i in range(120):
    f.write(str(i))
    for j in range(4):
        f.write("," + str(tmp[i, j]))
    f.write("\n")
f.close()
