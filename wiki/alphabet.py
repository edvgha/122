alphabet = {chr(int(0x0561)), 
        chr(int(0x0562)),
        chr(int(0x0563)),
        chr(int(0x0564)),
        chr(int(0x0565)),
        chr(int(0x0566)),
        chr(int(0x0567)),
        chr(int(0x0568)),
        chr(int(0x0569)),
        chr(int(0x056A)),
        chr(int(0x056B)),
        chr(int(0x056C)),
        chr(int(0x056D)),
        chr(int(0x056E)),
        chr(int(0x056F)),
        chr(int(0x0570)),
        chr(int(0x0571)),
        chr(int(0x0572)),
        chr(int(0x0573)),
        chr(int(0x0574)),
        chr(int(0x0575)),
        chr(int(0x0576)),
        chr(int(0x0577)),
        chr(int(0x0578)),
        chr(int(0x0579)),
        chr(int(0x057A)),
        chr(int(0x057B)),
        chr(int(0x057C)),
        chr(int(0x057D)),
        chr(int(0x057E)),
        chr(int(0x057F)),
        chr(int(0x0580)),
        chr(int(0x0581)),
        chr(int(0x0582)),
        chr(int(0x0583)),
        chr(int(0x0584)),
        chr(int(0x0585)),
        chr(int(0x0586)),
        chr(int(0x0587))}

lowercase_letters = {'AYB': chr(int(0x0561)), 
 'BEN': chr(int(0x0562)),
 'GIM': chr(int(0x0563)),
 'DA': chr(int(0x0564)),
 'ECH': chr(int(0x0565)),
 'ZA': chr(int(0x0566)),
 'EH': chr(int(0x0567)),
 'ET': chr(int(0x0568)),
 'TO': chr(int(0x0569)),
 'ZHE': chr(int(0x056A)),
 'INI': chr(int(0x056B)),
 'LIWN': chr(int(0x056C)),
 'XEH': chr(int(0x056D)),
 'CA': chr(int(0x056E)),
 'KEN': chr(int(0x056F)),
 'HO': chr(int(0x0570)),
 'JA': chr(int(0x0571)),
 'GHAD': chr(int(0x0572)),
 'CHEH': chr(int(0x0573)),
 'MEN': chr(int(0x0574)),
 'YI': chr(int(0x0575)),
 'NOW': chr(int(0x0576)),
 'SHA': chr(int(0x0577)),
 'VO': chr(int(0x0578)),
 'CHA': chr(int(0x0579)),
 'PEH': chr(int(0x057A)),
 'JHEH': chr(int(0x057B)),
 'RA': chr(int(0x057C)),
 'SEH': chr(int(0x057D)),
 'VEW': chr(int(0x057E)),
 'TIWN': chr(int(0x057F)),
 'REH': chr(int(0x0580)),
 'CO': chr(int(0x0581)),
 'YIWN': chr(int(0x0582)),
 'PIWR': chr(int(0x0583)),
 'KEH': chr(int(0x0584)),
 'OH': chr(int(0x0585)),
 'FEH': chr(int(0x0586)),
 'ECH_YIWN': chr(int(0x0587))}

modifiers = {chr(int(0x0559)),
        chr(int(0x055A)),
        chr(int(0x055B)),
        chr(int(0x055C)),
        chr(int(0x055D)),
        chr(int(0x055E)),
        chr(int(0x055F))}

modifiers1 = {'LEFT_HALF_RING': chr(int(0x0559)),
        'APOSTROPHE': chr(int(0x055A)),
        'EMPHASIS_MARK': chr(int(0x055B)),
        'EXCLAMATION_MARK': chr(int(0x055C)),
        'COMMA': chr(int(0x055D)),
        'QUESTION_MARK': chr(int(0x055E)),
        'ABBREVIATION_MARK': chr(int(0x055F))}

punctuations = {chr(int(0x0589)), 
        chr(int(0x058A)),
        '.', ',', ':',';','-',
        chr(int(0x058D))}

punctuation1 = {'FULL_STOP': chr(int(0x0589)), 
        'HYPHEN': chr(int(0x058A)),
        'ETERNITY_SIGN': chr(int(0x058D))}

brls = {'«', '[', '{', '<', '\'', '\"', '`'}
brrs = {'»', ']', '}', '>', '\'', '\"', '`'}

def is_arm_letter(c):
    return True if c in alphabet else False

def is_arm_punctuation(c):
    return True if c in punctuations else False

def is_arm_modifier(c):
    return True if c in modifiers else False

def is_arm_word(w):
    for l in w:
        if not is_arm_letter(l):
            return False
    return True

def is_brl(c):
    return True if c in brls else False

def is_brr(c):
    return True if c in brrs else False

def is_arm_shallow_word(w):
    letters = 0
    punctuation = 0
    digits = 0
    modifier = 0
    unknowns = 0
    brl = 0
    brr = 0
    i = 0
    for l in w:
        if is_arm_letter(l):
            letters += 1
        elif is_arm_punctuation(l) or '-' == l:
            punctuation += 1
        elif l >= '0' or l <= '9':
            digits += 1
        elif is_arm_modifier(l):
            modifier += 1
        elif is_brl(l) and i == 0:
            brl += 1
        elif is_brr(l) and i == (len(w) - 1):
            brr += 1
        else:
            unknowns += 1
            print (unknowns)
        i += 1
    if unknowns != 0:
        return False

    if len(w) / 2 >= letters:
        return False
        
    return True

def transform(w):
    '''
    FROM
    +---+-------+-------------------------------+-------+---+
    |ukw|letters|one-punctuation or one-modifier|letters|ukw|
    +---+-------+-------------------------------+-------+---+
    TO
    +-------+-------------------------------+-------+
    |letters|one-punctuation or one-modifier|letters|
    +-------+-------------------------------+-------+
    '''
    if not is_arm_shallow_word(w):
        return 'ignore_word'

    # Trim front
    i = 0
    while i < len(w) and (not is_arm_letter(w[i])):
            i += 1
    # Trim back 
    j = len(w) - 1
    while j >= 0 and (not is_arm_letter(w[j])):
            j -= 1

    k = i
    m = -1
    while k <= j:
        if not is_arm_letter(w[k]) and w[k] != '-':
            if m != -1:
                return 'ignore_word'
            else:
                m = k
        k += 1

    # We have only Arm letters
    if m == -1:
        return w[i:j + 1]

    # Returns longest half
    return w[i:m] if m - i > j - m else w[m + 1:j + 1]

def tokenize_and_transform(text):
    words = (text.lower()).split()
    transformed_text = []
    for w in words:
        transformed_text.append(transform(w))
    return ' '.join(transformed_text)
