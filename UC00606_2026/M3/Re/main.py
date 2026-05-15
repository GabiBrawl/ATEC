
import re

# exercicio 1 -
# mac = input("Insira o endereço MAC: ")
# pattern = r"([A-F0-9]{2}:){5}[A-F0-9]{2}"

# if re.fullmatch(pattern, mac, re.IGNORECASE):
#     print('Valid MAC')
# else:
#     print('Invalid MAC')


# exercicio 2 -
# def extract_email(input_string):
#     email_pattern = r"[\w\.-]+@[\w\.-]+\.\w+"
#     correspondence = re.search(email_pattern, input_string)
#     if correspondence:
#         print(f"Extracted Email: {correspondence.group()}")
#     else:
#         print("No email found.")

# input1 = "Please send the report to admin@empresa.pt before tomorrow."
# input2 = "No emails in this log file."

# print("Teste 1:")
# extract_email(input1)

# print("\nTeste 2:")
# extract_email(input2)


# exercicio 3 -

# def anonymizer(linha_log):
#     ip_pattern = r"\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}"

#     anonymized_line = re.sub(ip_pattern, "[REDACTED]", linha_log)
    
#     return anonymized_line

# test_input = "Intrusion detected from 192.168.1.50 at midnight."
# obtained_output = anonymizer(test_input)

# print("Input de Teste:")
# print(test_input)
# print("\nOutput Obtido:")
# print(obtained_output)


# exercicio 4 -
def string2list(input_string):
    regex_pattern = r"[,\s]+"
    return re.split(regex_pattern, input_string)

test_input = "apple, banana, orange,grape,melon, ERROR, 404, Not Found 10.0.0.1"
print("Output:")
print(string2list(test_input))