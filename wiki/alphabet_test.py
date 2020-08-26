import alphabet
import unittest

class TestAlphabet(unittest.TestCase):

    def test_upper(self):
        self.assertEqual('foo'.upper(), 'FOO')

    def test_is_arm_letter(self):
        self.assertTrue(alphabet.is_arm_letter('ր'))
        self.assertTrue(alphabet.is_arm_letter('և'))
        self.assertFalse(alphabet.is_arm_letter('՞'))
        self.assertFalse(alphabet.is_arm_letter('֊'))
        self.assertFalse(alphabet.is_arm_letter('x'))

    def test_is_arm_punctuation(self):
        self.assertFalse(alphabet.is_arm_punctuation('ր'))
        self.assertFalse(alphabet.is_arm_punctuation('A'))
        self.assertTrue(alphabet.is_arm_punctuation('֊'))
        self.assertTrue(alphabet.is_arm_punctuation('։'))

    def test_is_arm_modifier(self):
        self.assertFalse(alphabet.is_arm_modifier('ր'))
        self.assertFalse(alphabet.is_arm_modifier('k'))
        self.assertTrue(alphabet.is_arm_modifier('՞'))
        self.assertTrue(alphabet.is_arm_modifier('՜'))
        self.assertTrue(alphabet.is_arm_modifier('՛'))

    def test_is_arm_word(self):
        self.assertFalse(alphabet.is_arm_word('մ/ժ'))
        self.assertFalse(alphabet.is_arm_word('կգ:'))
        self.assertFalse(alphabet.is_arm_word('չանցած,'))
        self.assertTrue(alphabet.is_arm_word('համաձուլվածքների'))
        self.assertTrue(alphabet.is_arm_word('տուժեցին'))
        self.assertTrue(alphabet.is_arm_word('է'))
        self.assertTrue(alphabet.is_arm_word('մեծ'))
        self.assertTrue(alphabet.is_arm_word('մտքերի'))

    def test_transform(self):
        l = ["|ես", 
                "zfc-ն:վերոնշյալ", 
                "uk),դիաբետի", 
                "t-հանգույցներ", 
                "pkd1-հսկում", 
                "prp-ից:խոշոր", 
                "hcv-վիրուսի", 
                "iga,պենտամեր՝", 
                "ii-բիրկենաու,", 
                "ii:խոցը", 
                "images(չաշխատող", 
                "january)(անգլ.)ալեքսանդր", 
                "jit-կոմպիլյացիան", 
                "cham.:հոմանիշներ", 
                "a-ն,չնայած", 
                "a-ուղղանկյուաձև(մատրիցոն),", 
                "`պաշտոնապես", 
                "[կայսեր", 
                "[մասնակի])", 
                "[նրանց]", 
                "==«ինդիանա", 
                ":սակայն", 
                "(օյտյո-կաբու):", 
                "(օնտոգենեզ)."]
        expected = ["ես",
                "վերոնշյալ",
                "դիաբետի",
                "հանգույցներ",
                "հսկում",
                "խոշոր",
                "վիրուսի",
                "պենտամեր",
                "բիրկենաու",
                "խոցը",
                "չաշխատող",
                "ignore_word",
                "կոմպիլյացիան",
                "հոմանիշներ",
                "չնայած",
                "ուղղանկյուաձև",
                "պաշտոնապես",
                "կայսեր",
                "մասնակի",
                "նրանց",
                "ինդիանա",
                "սակայն",
                "օյտյո-կաբու",
                "օնտոգենեզ"
                ]
        idx = 0
        for w in l:
            self.assertEqual(expected[idx], alphabet.transform(w))
            idx += 1

    def test_tokenize_and_transform(self):
        text = '77 թվական, ոչ նահանջ տարի, ըստ գրիգորյան օրացույցի սկսում է ուրբաթ։ սա մեր թվարկության 77 թվականն է, i դարի 77-րդ տարին։ == դեպքեր == == ծնունդներ == == մահեր =='
        expected = 'ignore_word թվական ոչ նահանջ տարի ըստ գրիգորյան օրացույցի սկսում է ուրբաթ սա մեր թվարկության ignore_word թվականն ignore_word ignore_word դարի ignore_word տարին ignore_word դեպքեր ignore_word ignore_word ծնունդներ ignore_word ignore_word մահեր ignore_word'
        actual = alphabet.tokenize_and_transform(text)
        self.assertEqual(actual, expected)

if __name__ == '__main__':
    unittest.main()
