import cv2
import numpy as np


def reconstruct(imgName: str, modelName: str, k: int):
    img = cv2.imread(imgName, 0)
    model = np.load(modelName)

    mean = np.mean(model, axis=0)
    cov = np.cov(model.T)
    evals, evecs = np.linalg.eig(cov)

    # Sort eigenvectors and eigenvalues in descending order
    indices = np.argsort(evals)[::-1]
    evecs = evecs[:, indices]
    evals = evals[indices]

    # Choose top k eigenvectors
    evecs = evecs[:, :k]

    # Compute image vector
    img_vec = np.reshape(img, -1)
    mean = mean.reshape(1, -1)  # reshape to a row vector
    mean = np.tile(mean, (img_vec.shape[0], 1))  # repeat the row vector to match the number of pixels
    img_vec = (img_vec - mean).astype(np.uint8)
    
    # Compute reconstruction coefficients
    coeffs = np.dot(evecs.T, img_vec)

    # Reconstruct image from coefficients and eigenvectors
    reconstructed_img_vec = np.dot(evecs, coeffs) + mean
    reconstructed_img = np.reshape(reconstructed_img_vec, img.shape)

    return reconstructed_img
