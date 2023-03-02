from train import train
from reconstruct import reconstruct

def main():
    filename = './dataset/hand/shapes/shapes.asf'
    modelname = './model/mymodel.npy'
    train(filename, modelname)

    imginfo = './test/test.txt'
    reconstruct(imginfo, modelname, 10)


if __name__ == '__main__':
    main()
