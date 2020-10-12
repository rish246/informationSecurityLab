"""
Caesar Cipher Implementation python
"""
class CaesarCipher:
    def __init__(self, SHIFT):
        self.SHIFT = SHIFT

    
    # def is_capital(letter):

    def map_to_range(self, message):
        """
        Map a char string to characters having ascii (0, 25)
        """
        mapped_message = []
        for letter in message:
            if letter != ' ':
                map_value = ord(letter) - ord('a')
                # print(map_value)
                print(chr(map_value))
                mapped_message.append(chr(map_value))
            else:
                mapped_message.append(letter)
        
        return ''.join(mapped_message)



    def encrypt(self, message):
        """
        encrypts the message using caesar cipher
        
        => caesar cipher : 
            in caesar cipher, a letter in a message is replaced with a SHIFT places next to it.
        """
        mapped_message = self.map_to_range(message)

        encrypted_message = []

        for letter in mapped_message:
            if letter != " ":
                final_location = (ord(letter) + self.SHIFT) % 26
                encrypted_letter = chr(final_location)
                encrypted_message.append(encrypted_letter)
            else:
                encrypted_message.append(letter)

        return ''.join(encrypted_message)


    def decrypt(self, encoded_message):
        mapped_message = self.map_to_range(encoded_message)

        original_message = []

        for letter in mapped_message:
            if letter != " ":
                final_position = ord(letter) - self.SHIFT
                if final_position < 0:
                    final_position += 26

                original_message.append(chr(final_position))
            else:
                original_message.append(letter)

        return "".join(original_message)
                







def main():
    message = "this is a message"

    SHIFT = 4
    caesar_cipher = CaesarCipher(SHIFT)

    encrypted_text = caesar_cipher.encrypt(message)
    print(encrypted_text)

    original_message = caesar_cipher.decrypt(encrypted_text)
    print(original_message)

main()