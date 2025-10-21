from sklearn.model_selection import train_test_split
from sklearn.datasets import load_breast_cancer
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler


# this file contains all the function of the Linear regression needed using in scikit-learn linear regression model
# I will use some of the library that include numpy
import numpy as np

# Sigmoid function
def sigmoid(z) :
    return 1 /  (1 + np.exp(-z))

    
    
# Likelihood function for compute how different between the prediction and labeled data
# this function will heavily penalize predictions that are both confident( high probability) but wrong
def compute_cost(A : np.matrix, y : np.matrix) -> float :
    epsilon = 1e-9
    m = y.shape[0]
    
    cost = (-1 / m) * np.sum(y * np.log(A + epsilon) + (1 - y) * np.log(1 - A + epsilon))

    return cost



# initialize 2 vectors for the begining of the training process
# this function returns a vector of the Weight and a vetor of Bias
def init_parameter(n_features : int) -> tuple[np.ndarray, float] :
    A = np.zeros((n_features, 1))
    b =  0.0

    return A, b



# compute the way to change the parameter Weight & Bias
def compute_gradient(X, A, y):
    m = X.shape[0]
    
    # The gradient calculations we discussed before
    # A - y is the error, shape (m, 1)
    # X.T is (n, m)
    # np.dot(X.T, (A - y)) gives shape (n, 1)
    dw = (1/m) * np.dot(X.T, (A - y)) 
    
    # db is the average of the error
    db = (1/m) * np.sum(A - y)
    
    return dw, db



# Find the weight and bias base on the 
def fit(X_train: np.array, y_train: np.array, learning_rate: float, n_iteration: int):
    # Get number of samples (m) and features (n) from X_train's shape
    # m = number of rows (samples)
    # n = number of columns (features)
    m, n_features = X_train.shape
    
    # 1. FIX: Initialize parameters using n_features, NOT n_iteration
    w, b = init_parameter(n_features)
    # 2. FIX: Use a simple list to record cost
    cost_record = [] 
    
    for i in range(n_iteration):
        # --- FORWARD PASS (on the *entire* dataset) ---
        
        # 3. MAJOR FIX: Calculate Z for ALL samples at once.
        # X_train shape: (m, n_features)
        # w shape:       (n_features, 1)
        # np.dot result: (m, 1)
        Z = np.dot(X_train, w) + b
        
        # A will also have shape (m, 1)
        A = sigmoid(Z)
        
        # --- COST & BACKWARD PASS ---
        
        # 4. FIX: Calculate cost, not 'put' predictions
        cost = compute_cost(A, y_train)
        cost_record.append(cost)
        
        # This function now gets the correct inputs
        # X_train: (m, n_features)
        # A:       (m, 1)
        # y_train: (m, 1)
        dw, db = compute_gradient(X_train, A, y_train)
        
        # --- PARAMETER UPDATE ---
        # These lines were already correct!
        w = w - learning_rate * dw
        b = b - learning_rate * db
        
    # 5. FIX: Return a tuple, which is standard
    return w, b, cost_record



#prediction function
def predict(X_test : np.matrix, w, b, threshold=0.5) -> bool:
    Z =  np.dot(X_test, w)+ b
    A = sigmoid(Z)
    
    predictions = (A > threshold).astype(int)

    return predictions



X, y = load_breast_cancer(return_X_y= True)
y = y.reshape(-1, 1)

# Split Training sample & testing sample
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.8, random_state=23)

# Scale the Data
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Training
w,b,cost = fit(X_train, y_train,0.075, 13656)

# Test
acc = accuracy_score(y_test, predict(X_test,w,b,),) * 100

print(f"Logistics Model Accuracy: {acc : .2f}%")