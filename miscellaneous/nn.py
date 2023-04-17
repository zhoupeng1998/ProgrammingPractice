# A neural network implementation from scratch to classify circle, gaussian, spiral, and xor dataset

import sys
import numpy as np
import time

def sigmoid(Z):
    A = 1/(1+np.exp(-Z))
    param = Z
    return A, param

def relu(Z):
    A = np.maximum(0,Z)
    param = Z 
    return A, param

def softmax(Z):
    A = np.exp(Z) / np.sum(np.exp(Z), axis=1)
    param = Z
    return A, param

def relu_gradient(dA, param):
    Z = param
    dZ = np.array(dA, copy=True)
    dZ[Z <= 0] = 0
    return dZ

def sigmoid_gradient(dA, param):
    Z = param
    s = 1/(1+np.exp(-Z))
    dZ = dA * s * (1-s)
    return dZ

def softmax_gradient(dA, param):
    Z = param
    s = np.exp(Z) / np.sum(np.exp(Z), axis=0)
    dZ = dA * s * (1-s)
    return dZ

# initialize parameters
def init_params(n_x, n_h1, n_h2, n_y):
    np.random.seed(1)
    W1 = np.random.randn(n_h1, n_x)
    b1 = np.zeros((n_h1, 1))
    W2 = np.random.randn(n_h2, n_h1)
    b2 = np.zeros((n_h2, 1))
    W3 = np.random.randn(n_y, n_h2)
    b3 = np.zeros((n_y, 1))
    return W1, b1, W2, b2, W3, b3

# linear forward function
def linear_forward(A, W, b):
    Z = np.dot(W, A) + b

    param = (A, W, b)
    return Z, param

# linear activation forward function
def linear_activation_forward(A_prev, W, b, activation):
    if activation == "sigmoid":
        Z, linear_param = linear_forward(A_prev, W, b)
        A, activation_param = sigmoid(Z)
    elif activation == "relu":
        Z, linear_param = linear_forward(A_prev, W, b)
        A, activation_param = relu(Z)
    else:
        raise Exception('activation function not supported')
    
    assert (A.shape == (W.shape[0], A_prev.shape[1]))
    param = (linear_param, activation_param)
    return A, param

# read data
def read_data(train_data_file, train_label_file, test_data_file):
    train_data = np.genfromtxt(train_data_file, delimiter=',')
    test_data = np.genfromtxt(test_data_file, delimiter=',')

    train_x = train_data[:, 0]
    train_y = train_data[:, 1]
    test_x = test_data[:, 0]
    test_y = test_data[:, 1]

    train_x = np.sin(train_x).reshape(train_data.shape[0], 1)
    train_y = np.sin(train_y).reshape(train_data.shape[0], 1)

    test_x = np.sin(test_x).reshape(test_data.shape[0], 1)
    test_y = np.sin(test_y).reshape(test_data.shape[0], 1)

    train_data = np.append(train_data, train_x, axis=1)
    train_data = np.append(train_data, train_y, axis=1)
    train_data = train_data.T
    
    test_data = np.append(test_data, test_x, axis=1)
    test_data = np.append(test_data, test_y, axis=1)
    test_data = test_data.T

    train_label = np.genfromtxt(train_label_file, delimiter=',').reshape(1, train_data.shape[1])

    return train_data, train_label, test_data

# compute cost
def compute_cost(P, Y):
    m = Y.shape[1]
    delta = 1e-7
    cost = -1/m * np.sum(Y * np.log(P + delta) + (1-Y) * np.log(1-P + delta))
    cost = np.squeeze(cost)
    assert(cost.shape == ())
    return cost

def linear_gradient(dZ, param):
    A_prev, W, b = param
    m = A_prev.shape[1]
    dW = 1/m * np.dot(dZ, A_prev.T)
    db = 1/m * np.sum(dZ, axis=1, keepdims=True)
    dA_prev = np.dot(W.T, dZ)
    assert (dA_prev.shape == A_prev.shape)
    assert (dW.shape == W.shape)
    assert (db.shape == b.shape)
    return dA_prev, dW, db

def linear_activation_gradient(dA, param, activation):
    linear_param, activation_param = param
    if activation == "relu":
        dZ = relu_gradient(dA, activation_param)
        dA_prev, dW, db = linear_gradient(dZ, linear_param)
    elif activation == "sigmoid":
        dZ = sigmoid_gradient(dA, activation_param)
        dA_prev, dW, db = linear_gradient(dZ, linear_param)
    else:
        raise Exception('activation function not supported')
    return dA_prev, dW, db

# forward propagation
def forward_propagation(X, params):
    W1, b1, W2, b2, W3, b3 = params
    A1, param1 = linear_activation_forward(X, W1, b1, activation='relu')
    A2, param2 = linear_activation_forward(A1, W2, b2, activation='relu')
    A3, param3 = linear_activation_forward(A2, W3, b3, activation='sigmoid')
    params = (param1, param2, param3)
    return A3, params

def backward_propagation(P, Y, params):
    param1, param2, param3 = params
    Y = Y.reshape(P.shape)
    delta = 1e-7
    dP = - (np.divide(Y, P + delta) - np.divide(1 - Y, 1 - P + delta))
    dA3, dW3, db3 = linear_activation_gradient(dP, param3, activation='sigmoid')
    dA2, dW2, db2 = linear_activation_gradient(dA3, param2, activation='relu')
    dA1, dW1, db1 = linear_activation_gradient(dA2, param1, activation='relu')
    return dW1, db1, dA1, dW2, db2, dA2, dW3, db3, dA3

def update_parameters(params, grads, learning_rate):
    W1, b1, W2, b2, W3, b3 = params
    dW1, db1, dA1, dW2, db2, dA2, dW3, db3, dA3 = grads
    W1 = W1 - learning_rate * dW1
    b1 = b1 - learning_rate * db1
    W2 = W2 - learning_rate * dW2
    b2 = b2 - learning_rate * db2
    W3 = W3 - learning_rate * dW3
    b3 = b3 - learning_rate * db3
    return W1, b1, W2, b2, W3, b3

# main
if __name__ == '__main__':
    W1, b1, W2, b2, W3, b3 = init_params(4, 6, 6, 1)
    train_data, train_label, test_data = read_data(sys.argv[1], sys.argv[2], sys.argv[3])

    t1 = time.time()

    for i in range(60000):
        A, param = forward_propagation(train_data, (W1, b1, W2, b2, W3, b3))
        cost = compute_cost(A, train_label)
        grads = backward_propagation(A, train_label, param)
        W1, b1, W2, b2, W3, b3 = update_parameters((W1, b1, W2, b2, W3, b3), grads, 0.01)

    t2 = time.time()

    A, _ = forward_propagation(test_data, (W1, b1, W2, b2, W3, b3))
    A[A >= 0.5] = 1
    A[A < 0.5] = 0

    test_label = np.genfromtxt('public/spiral_test_label.csv', delimiter=',').reshape(1, test_data.shape[1])

    np.savetxt('test_predictions.csv', A, fmt="%d", delimiter="\n")

    print(test_label.shape)
    print(A.shape)

    wrong = 0
    for i in range(len(test_label[0])):
        if test_label[0][i] != A[0][i]:
            wrong += 1
    print("Accuracy: ", (len(test_label[0]) - wrong) / len(test_label[0]))

    print("Time: ", t2 - t1)