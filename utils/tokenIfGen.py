tokens =  [
    "exit",
    "integer",
    "begin_paren",
    "end_paren",
    "begin_curly",
    "end_curly",
    "def",
    "func",
    "eq",
    "plus",
    "minus",
    "star",
    "forward_slash",
    "modulus",
    "whitespace",
]

for i in tokens:
    print(
        f'''
        if (type == TokenType::{i}) {{
            return("{i}");
        }}
        '''
    )