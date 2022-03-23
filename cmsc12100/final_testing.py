
def extract_answers(puzzle):
    N = len(puzzle)
    answers = []
    for i in range(N):
        current_string = ""
        current_pos = (i, 0)

        for j in range(N):
            if puzzle[i][j] != '#':
                current_string += puzzle[i][j]
                if j == 0 or puzzle[i][j-1] == '#':
                    current_pos = (i, j)
                if j == N-1:
                    answers.append((current_string, current_pos))

            else:
                if len(current_string) > 0:
                    answers.append((current_string, current_pos))
                current_string = ""

    return answers
