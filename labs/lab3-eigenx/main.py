from train import train
from reconstruct import reconstruct


def main():
    filename = './dataset/hand/shapes/shapes.asf'
    modelname = './model/mymodel.npy'
    train(filename, modelname)

    imgname = './test/test.jpg'
    imginfo = './test/info.txt'
    reconstruct(imgname, modelname, imginfo)


if __name__ == '__main__':
    main()
