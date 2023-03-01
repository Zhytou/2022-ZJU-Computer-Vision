from train import train
from reconstruct import reconstruct

def main():
    filename = './dataset/hand/shapes/shapes.asf'
    modelname = './model/mymodel.npy'
    train(filename, modelname)

    imgname = './test/test.jpg'
    reconstruct(imgname, modelname, 10)


if __name__ == '__main__':
    main()
