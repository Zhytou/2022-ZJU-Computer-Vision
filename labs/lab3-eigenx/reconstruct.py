import cv2
import numpy as np


def reconstruct(imgName: str, modelName: str, imgInfo):
    img = cv2.imread(imgName, 0)
    model = np.load(modelName)

    mean = np.mean(model, axis=0)
    cov = np.cov(model.T)
    evals, evecs = np.linalg.eig(cov)
