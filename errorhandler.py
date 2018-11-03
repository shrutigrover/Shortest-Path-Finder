class Errors:
    def checkStreetFormat(self,street_name):
        if all(x.isspace() or x.isalpha() for x in street_name):
            return True
        else:
            return False

    def checkInput(self, input_string):
        start_pt = input_string.find("\"")
        end_pt = input_string.find("\"", start_pt + 1)
        check_spaces = (start_pt != -1 and end_pt != -1 and input_string[start_pt-1].isspace() and input_string[end_pt+1].isspace())
        opening_brackets = input_string.count("(")
        closing_brackets = input_string.count(")")
        
        if input_string[0] == 'a' or input_string[0] == 'c':
            if check_spaces and (opening_brackets == closing_brackets):
                if (input_string[0] == 'a' or input_string[0] == 'c') and opening_brackets > 0:
                    return True
                else:
                    return False
                return True
            else:
                return False

        if input_string[0] == 'r':

            if start_pt == -1 or end_pt == -1 or not input_string[end_pt+1:].isspace() :
                return False
        return True
