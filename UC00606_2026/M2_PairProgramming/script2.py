MAX_FAILURES = 3
EVENT_SUCCESS = "S" 
EVENT_FAILURE = "F"

event = input("Enter the event sequence (S for success, F for failure): ")
upper_event = event.upper()  # converte a sequência para maiúsculas para comparação
allowed = set([EVENT_SUCCESS, EVENT_FAILURE])  # conjunto de eventos permitidos
invalid_char = False  # flag para detectar caracteres inválidos

for char in upper_event:
    if char not in allowed:
        invalid_char = True
        break

if invalid_char:
    print("Invalid character found in event sequence.")
    