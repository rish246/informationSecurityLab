"""
Hill Cipher Python implementation
"""
import math
import numpy as np
import sympy

# plain_text = "attack"


class HillCipher:

    def __init__(self, key):
        self.key = key


    ##################################################################################
    ########## helper functions ######################################################
    def get_col_vectors(self, plain_text):
        """
        Convert text into column vectors
        e.g => plaintText = "abcd"
            => colVectors = [ ["a", "b"], ["c", "d"] ]
            => adjascent letters go into same column vector
        """
        list_column_vectors = []
        cur_col_vector = []
        
        len_cur_col_vector = 0

        for letter in plain_text:
            cur_col_vector.append(ord(letter) - ord('a'))
            len_cur_col_vector += 1
            if len_cur_col_vector == self.key.shape[0]:

                col_vector_as_array = np.array(cur_col_vector)
                # print(col_vector_as_array)

                list_column_vectors.append(col_vector_as_array)
                cur_col_vector.clear()
                len_cur_col_vector = 0
        return list_column_vectors

    def convert_col_vectors(self, list_column_vectors, key):
        """
        encrypt/decrypt the column vectors
        if encrypted => decrypt
        else encrypt
        """
        list_converted_col_vectors = []

        for column_vector in list_column_vectors:
            converted_col_vector = np.dot(key, column_vector) % 26
            # print(encrypted_col_vector)
            list_converted_col_vectors.append(converted_col_vector)
        
        return list_converted_col_vectors


    def get_converted_text(self, list_encrypted_col_vectors):
        """ 
        Convert the column vectors back to string form
        e.g => [["a", "b"], ["c", "d"]] ==> "abcd"
        """
        converted_text = []

        for col_vector in list_encrypted_col_vectors:
            first_char, second_char = col_vector
            converted_text.append(chr(math.floor(first_char) + ord('a')))
            converted_text.append(chr(math.floor(second_char) + ord('a')))


        converted_text = ''.join(converted_text)
        return converted_text


    ##############################################################################
    ############### main encryption code #########################################
    def encrypt(self, plain_text):
        """
        Encrypt the recieved plain text

        """
        list_column_vectors = []

        # key = np.array([[2, 3], [3, 6]])

        list_column_vectors = self.get_col_vectors(plain_text)


        list_encrypted_col_vectors = self.convert_col_vectors(list_column_vectors, self.key)


        encrypted_text = self.get_converted_text(list_encrypted_col_vectors)

        return encrypted_text


    ###########################################################################
    ###################### main decryption code ##############################
    def inverse(self, matrix):
        """
        compute inverse of a given matrix with mod(26)
        i.e => return inverse(matrix) mod(26)

        """
        determinant = int(np.linalg.det(matrix))

        determinant_inv = int(sympy.invert(determinant, 26))

        matrix_adjascent = np.linalg.inv(matrix) * determinant

        matrix_inv = determinant_inv * matrix_adjascent % 26

        matrix_inv = matrix_inv.astype(int)

        return matrix_inv


    def decrypt(self, encrypted_text):
        """
        decrypt the recieved encrypted text
        """
        key_inverse = self.inverse(self.key)

        # print(key_inverse)
        list_col_vectors = self.get_col_vectors(encrypted_text)

        list_decrypted_col_vectors = self.convert_col_vectors(list_col_vectors, key_inverse)

        original_text = self.get_converted_text(list_decrypted_col_vectors)

        # print(original_text)
        return original_text




def main():
    """ 
    Main function

    """
    key = np.array([[2, 3], [3, 6]])

    hill_cipher = HillCipher(key)
    plain_text = "plants"

    print(f'Orignal Message : {plain_text}')

    encrypted_text = hill_cipher.encrypt(plain_text)

    print(f'Encrypted Message : {encrypted_text}')

    original_text = hill_cipher.decrypt(encrypted_text)

    print(f'Decrypted Message : {original_text}')


main()

