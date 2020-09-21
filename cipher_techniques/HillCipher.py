import numpy as np
import math
import sympy

plain_text = "attack"

def get_col_vectors(plain_text, key):
    list_column_vectors = []
    cur_col_vector = []
    
    len_cur_col_vector = 0
    
    for letter in plain_text:
        cur_col_vector.append(ord(letter) - ord('a'))
        len_cur_col_vector += 1
        if(len_cur_col_vector == key.shape[0]):

            col_vector_as_array = np.array(cur_col_vector)
            # print(col_vector_as_array)

            list_column_vectors.append(col_vector_as_array)
            cur_col_vector.clear()
            len_cur_col_vector = 0
    return list_column_vectors

def encrypt_col_vectors(list_column_vectors, key):
    list_encrypted_col_vectors = []

    for column_vector in list_column_vectors:
        encrypted_col_vector = np.dot(key, column_vector) % 26
        # print(encrypted_col_vector)
        list_encrypted_col_vectors.append(encrypted_col_vector)
    
    return list_encrypted_col_vectors


def get_encrypted_text(list_encrypted_col_vectors):
    ciphered_text = []

    for col_vector in list_encrypted_col_vectors:
        first_char, second_char = col_vector
        ciphered_text.append(chr(math.floor(first_char) + ord('a')))
        ciphered_text.append(chr(math.floor(second_char) + ord('a')))


    encrypted_text = ''.join(ciphered_text)

    return encrypted_text

def encrypt(plain_text):
    list_column_vectors = []

    key = np.array([[2, 3], [3, 6]])

    list_column_vectors = get_col_vectors(plain_text, key)


    list_encrypted_col_vectors = encrypt_col_vectors(list_column_vectors, key)


    encrypted_text = get_encrypted_text(list_encrypted_col_vectors)


    # print(encrypted_text)
    return encrypted_text



def inverse(matrix):
    determinant = int(np.linalg.det(matrix))

    determinant_inv = int(sympy.invert(determinant, 26))

    matrix_adjascent = np.linalg.inv(matrix) * determinant

    matrix_inv = determinant_inv * matrix_adjascent % 26

    matrix_inv = matrix_inv.astype(int)

    return matrix_inv
def decrypt_col_vectors(list_col_vectors, key):
    list_decrypted_col_vectors = []

    # key_inverse = np.linalg.inv(key)
    key_inverse = inverse(key)

    for column_vector in list_col_vectors:

        decrypted_col_vector = np.dot(key_inverse, column_vector) % 26
        # print(encrypted_col_vector)
        list_decrypted_col_vectors.append(decrypted_col_vector)
    
    return list_decrypted_col_vectors

def decrypt(plain_text):

    key = np.array([[2, 3], [3, 6]])

    key_inverse = np.linalg.inv(key)

    list_col_vectors = get_col_vectors(plain_text, key)

    list_decrypted_col_vectors = decrypt_col_vectors(list_col_vectors, key)

    # print(list_decrypted_col_vectors)
    print(key_inverse)
# ## refactor this code 
    original_text = get_encrypted_text(list_decrypted_col_vectors)

    print(original_text)
    return plain_text
## use functions 

cypher_text = encrypt(plain_text)

print(cypher_text)
original_text = decrypt(cypher_text)