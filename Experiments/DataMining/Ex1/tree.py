import pandas as pd
from pylab import *

train = pd.read_csv('first_round_training_data.csv')
test = pd.read_csv('first_round_testing_data.csv')
test = test[
    ['Parameter1', 'Parameter2', 'Parameter3', 'Parameter4', 'Parameter5', 'Parameter6', 'Parameter7', 'Parameter8',
     'Parameter9', 'Parameter10']].values.tolist()

featherlist = ["Parameter" + str(i) for i in range(1, 11)]
Q_label = ['Excellent', 'Good', 'Pass', 'Fail']
# print(featherlist)
d = ["Parameter" + str(i) for i in range(1, 11)]
d.append("Quality_label")  # 在末尾添加质量列
X_train = train[d].values.tolist()  # 转换成列表


# 决策树---统计每种label的个数
def counts(rows):
    results = {}
    for row in rows:
        r = row[len(row) - 1]
        if r not in results:
            results[r] = 0
        results[r] += 1
    return results


# 计算熵值
def entropy(rows):
    results = counts(rows)
    ent = 0.0
    for r in results.keys():
        # 概率分布
        p = results[r] / len(rows)
        ent = ent - p * math.log(p, 2)
    return ent


# 基尼系数
def gini(rows):
    total = len(rows)
    count = counts(rows)
    imp = 0
    for k in count.keys():
        p = float(count[k]) / total
        imp = imp + p * (1 - p)
    return imp


# 定义节点的属性
class decisionNode:
    def __init__(self, col=-1, value=None, results=None, tb=None, fb=None):
        self.col = col  # col是待检验的判断条件所对应的列索引值
        self.value = value  # value对应于为了使结果为True，当前列必须匹配的值
        self.results = results  # 保存的是针对当前分支的结果，它是一个字典
        self.tb = tb  # desision node,对应于结果为true时，树上相对于当前节点的子树上的节点
        self.fb = fb  # desision node,对应于结果为false时，树上相对于当前节点的子树上的节点


# 对数据集进行拆分
def divivset(rows, column, value):
    split_function = lambda row: row[column] >= value
    set1 = [row for row in rows if split_function(row)]
    set2 = [row for row in rows if not split_function(row)]
    return set1, set2


def buildtree(rows, scoref=entropy):
    if len(rows) == 0:
        return decisionNode()
    current_score = scoref(rows)

    best_gain = 0
    best_criteria = None
    best_sets = None

    column_count = len(rows[0]) - 1
    for col in range(0, column_count):
        column_values = {}
        for row in rows:
            column_values[row[col]] = 1
        # 数据集拆分
        for value in column_values.keys():
            (set1, set2) = divivset(rows, col, value)
            p = float(len(set1)) / len(rows)
            # 计算基尼系数
            gain = current_score - p * scoref(set1) - (1 - p) * scoref(set2)
            if gain > best_gain and len(set1) > 0 and len(set2) > 0:
                best_gain = gain
                best_criteria = (col, value)
                best_sets = (set1, set2)
    if best_gain > 0:
        trueBranch = buildtree(best_sets[0])
        falseBranch = buildtree(best_sets[1])
        return decisionNode(col=best_criteria[0], value=best_criteria[1],
                            tb=trueBranch, fb=falseBranch)
    else:
        return decisionNode(results=counts(rows))


def classify(observation, tree):
    if tree.results is not None:
        return tree.results
    else:
        v = observation[tree.col]
        branch = None
        if v >= tree.value:
            branch = tree.tb
        else:
            branch = tree.fb
        return classify(observation, branch)


print("begin build")
tree = buildtree(X_train)
print("build success")

# 测试
print("begin")
l = []
count = 0
o = 0
labelSet = {}
for t in test:
    label = classify(t, tree)
    label = list(label.keys())[0]
    # print(label)
    if label not in labelSet.keys():
        labelSet[label] = 0
    labelSet[label] += 1
    count = count + 1
    if count % 50 == 0:
        for item in Q_label:
            if item not in labelSet.keys():
                labelSet[item] = 0
        temp = []
        temp.append(labelSet['Excellent'] / (labelSet['Excellent'] + labelSet['Good'] + labelSet['Pass'] + labelSet['Fail']))
        temp.append(labelSet['Good'] / (labelSet['Excellent'] + labelSet['Good'] + labelSet['Pass'] + labelSet['Fail']))
        temp.append(labelSet['Pass'] / (labelSet['Excellent'] + labelSet['Good'] + labelSet['Pass'] + labelSet['Fail']))
        temp.append(labelSet['Fail'] / (labelSet['Excellent'] + labelSet['Good'] + labelSet['Pass'] + labelSet['Fail']))

        l.append(temp)
        labelSet.clear()

with open('ans-tree.csv', 'w') as f:
    for i in range(len(l)):
        f.write(str(i) + ',' + str(l[i][0]) + ',' + str(l[i][1]) + ',' + str(l[i][2]) + ',' + str(l[i][3]) + '\n')
