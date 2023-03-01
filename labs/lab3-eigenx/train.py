import numpy as np
import scipy.linalg


def read(dataset: str):
    shapes = []
    fp = open(dataset)
    for i in range(int(fp.readline())):
        line = fp.readline()
        points = []
        for point in line.split():
            points.append(float(point))
        shapes.append(points)

    return shapes


# [xi, ..., yi, ... ] -> [[xi, ...], [yi, ...]]
def unmake_1d(points):
    npoints = []
    for i in range(0, points.shape[0]//2):
        npoints.append([points[i], points[i+points.shape[0]//2]] )
    return np.array(npoints)


# [[xi, ...], [yi, ...]] -> [xi, ..., yi, ... ]
def make_1d(points):
    return np.concatenate((points[:, 0], points[:, 1])).reshape(-1)


def train(dataset: str, model: str):
    # 读取图片
    shapes = np.array(read(dataset))
    print(shapes[0].shape)

    # 求所有图片特征点平均值
    meanShapes = np.mean(shapes, axis=0)

    normalizedShapes = shapes
    # 遍历每个图片（每行）
    for i in range(shapes.shape[0]):
        # PCA主成分分析
        _, mtx, _ = scipy.spatial.procrustes(unmake_1d(meanShapes), unmake_1d(shapes[i]))
        normalizedShapes[i] = make_1d(mtx)

    np.save(model, normalizedShapes)
