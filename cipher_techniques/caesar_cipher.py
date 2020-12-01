"""
Caesar Cipher Implementation python
"""
class CaesarCipher:
    def __init__(self, SHIFT):
        self.SHIFT = SHIFT

    
    # def is_capital(letter):



    def encrypt(self, message):
        """
        encrypts the message using caesar cipher
        
        => caesar cipher : 
            in caesar cipher, a letter in a message is replaced with a SHIFT places next to it.
        """

        encrypted_message = []

        # 80 -> 100
        # t -> 19
        # 179 -> 19
        # 
        for letter in message:
            final_letter_location = (ord(letter) + self.SHIFT) % ord('z')

            # if final_letter_location < ord('a') final_letter_location += ord('a')
            if(final_letter_location < ord('a')):
                final_letter_location += ord('a')
            encrypted_letter = chr(final_letter_location)
            encrypted_message.append(encrypted_letter)
        
        return ''.join(encrypted_message)


    # 80 -> 100
    # 78
    # 78 < 80 ? 98 : 78
    def decrypt(self, encoded_message):

        original_message = []

        for letter in encoded_message:
            original_letter_location = (ord(letter) - self.SHIFT)
            if original_letter_location < ord('a'):
                original_letter_location += 25      
            original_message.append(chr(original_letter_location))

        return "".join(original_message)
                







def main():
    plain_text = "attackatthedawn"

    SHIFT = 4
    caesar_cipher = CaesarCipher(SHIFT)

    print(f'Original Message : {plain_text}')
    cipher_text = caesar_cipher.encrypt(plain_text)
    print(f'Encrypted Message : {cipher_text}')


    original_message = caesar_cipher.decrypt(cipher_text)
    print(f'Decrypted Message : {original_message}')

main()

# w --> {