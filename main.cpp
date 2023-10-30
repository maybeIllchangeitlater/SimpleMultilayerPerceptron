#include <iostream>
#include "MLP.h"


int main() {
    s21::DataLoader d(784, 26);
    d.FileToData(s21::DataLoader::kTest, true);
    auto test_data = d.Data();
    std::uniform_int_distribution<size_t> dist(0, d.MaximumTests() - 26);

    d.FileToData(s21::DataLoader::kTrain, true);
    std::random_device rd;
    std::mt19937 gen(rd());

    s21::MLP biba(std::vector<size_t>({784, 240, 84,  26, 26}), d, 0.03);
    for(int i = 0; i <30; ++i) {
        if(i == 13) biba.AdjustLr(0.003);
        if(i == 16) biba.AdjustLr(0.007);
        if(i == 19) biba.AdjustLr(0.005);
        if(i == 22) biba.AdjustLr(0.001);
        if(i == 25) biba.AdjustLr(0.0005);
        biba.GradientDescent(150, 150);
        auto batch = d.CreateSample(200, dist(gen));
        size_t correct = 0;
        for (const auto &p: batch) {
            correct += biba.Predict(p);
        }
        std::cout << "correctly guessed " << correct << "out of " << batch.size() << " examples" << std::endl;
    }
    ///test
    std::cout << "it's testing time" << std::endl;
//    std::random_device rd; // obtain a random number from hardware
//    std::mt19937 gen(rd()); // seed the generator

    d.FileToData(s21::DataLoader::kTest, true);
    auto & test = d.Data();
    size_t correct = 0;
    for(const auto& p : test){
        correct += biba.Predict(p);
    }
    std::cout << "correctly guessed " << correct << "out of " << d.MaximumTests() <<" examples" << std::endl;


    ///correctly guessed 7382out of 14800 examples
    ///784, 150, 26, 26 topology
    ///0.03 lr
    ///8 batches 100 epochs 150 size

    ///remove 2 more
//    s21::MyLittleAboba(sample, )
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<unsigned> distribution_letters(0, 25);
//    std::uniform_real_distribution<double> distribution_weights(0, 0.01);
//
//    d.FileToData(s21::DataLoader::kTrain);
//    auto sample = d.CreateSample(200);
//
//    ///init from sample
////        Eigen::MatrixXd input(sample[0][0].data(), 784, 1);
//    Eigen::MatrixXd input(784, 1);
//    for(unsigned i = 0; i < 784; ++i){
//        input(i,0) = sample[0][0][i]; ///just an example whats inside initfunc
//        ///vector of doubles will need to be passed in
//    } ///will need to create vector of matrixes like this or prehaps load data into them
//
//
//    ///init parametrs
//        Eigen::MatrixXd W1(26, 784);
//        for(unsigned i = 0; i < W1.rows(); ++i){
//            for(unsigned j = 0; j < W1.cols(); ++j){
//                W1(i, j) = distribution_weights(gen);
//            }
//        }
//        Eigen::MatrixXd b1(26, 1);
//        for(unsigned i = 0; i < b1.rows(); ++i){
//            for(unsigned j = 0; j < b1.cols(); ++j){
//                b1(i, j) = distribution_weights(gen);
//            }
//        }
//        Eigen::MatrixXd W2(26, 26);
//        for(unsigned i = 0; i < W2.rows(); ++i){
//            for(unsigned j = 0; j < W2.cols(); ++j){
//                W2(i, j) = distribution_weights(gen);
//            }
//        }
//        Eigen::MatrixXd b2(26, 1);
//        for(unsigned i = 0; i < b2.rows(); ++i){
//            for(unsigned j = 0; j < b2.cols(); ++j){
//                b2(i, j) = distribution_weights(gen);
//            }
//        }
//
//        ///forward prop
//        Eigen::MatrixXd Z1 = W1*input + b1;
//        Eigen::MatrixXd A1 = 1.0 / (1.0 + (-Z1).array().exp()); ///sigm
//        Eigen::MatrixXd Z2 = W2 * A1 + b2;
//        Eigen::MatrixXd A2 = 1.0 / (1.0 + (-Z2).array().exp());
//
//        ///output vector thing needed
//        Eigen::MatrixXd Y(Eigen::MatrixXd::Zero(26, 1));
//        Y(0, 0) = 1;
//
//        ///backprop
//        unsigned m = Y.size();
//        Eigen::MatrixXd dZ2 = A2 - Y;
//        Eigen::MatrixXd dW2 = (1.0 / m) * dZ2 *A1.transpose();
//        Eigen::MatrixXd db2 = (1.0 / m) * dZ2;
//        Eigen::MatrixXd dZ1 = (W2.transpose() * dZ2).array() * (A1.array() * (1 - A1.array())); ///sigm deriv
//        Eigen::MatrixXd dW1 = (1.0 / m) * dZ1 *input.transpose();
//        Eigen::MatrixXd db1 = (1.0 / m) * dZ1;
//
//        ///update
//        double alpha = 0.5;
//        W1 -= alpha * dW1;
//        b1 -= alpha * db1;
//        W2 -= alpha * dW2;
//        b2 -= alpha * db2;


    return 0;
}

