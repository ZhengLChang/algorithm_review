/*
   https://leetcode-cn.com/problems/longest-duplicate-substring/
   */
#include <iostream>
#include <unordered_set>
#include <set>
#include <utility>
#include <cmath>
#include "../util.h"

using namespace std;

class Solution {
public:
    string longestDupSubstring(string s){
        string longest_str = "";
        string substring = "";
        int substr_len = 0;
        int j = 0;
        int s_size = s.size();
        if(s_size <= 1)
        {
            return "";
        }
        unordered_set<string> sub_set(1240);
        int win_len = s_size - 1;
        int i = 0;
        for(; win_len >= 1; --win_len)
        {
            sub_set.clear();
            for(i = 0; i + win_len <= s_size; ++ i)
            {
                substring = s.substr(i, win_len);
                if(sub_set.find(substring) == sub_set.end())
                {
                    sub_set.insert(substring);
                }
                else
                {
                    //cout << "sub_set.size() : " << sub_set.size() << endl;
                    return substring;
                }
            }
        }
        return "";
#if 0
        for(int i = 0; i < s.size(); ++i)
        {
            if(longest_str.size() > (s.size() - i))
            {
                continue;
            }
            for(j = s.size(); j < s.size(); ++j)
            {
                substr_len = (j - i + 1);
                if(longest_str.size() > substr_len)
                {
                    continue;
                }
                //cout << "(" << longest_str.size() << ", " << (j - i + 1) << ")" << endl;
                substring = s.substr(i, substr_len);
                if(sub_set.find(substring) == sub_set.end())
                {
                    sub_set.insert(substring);
                }
                else if(substring.size() > longest_str.size())
                {
                    longest_str = substring;
                    if(longest_str.size() == s.size() - 1)
                    {
                        return longest_str;
                    }

                }
            }
        }
        return longest_str;
#endif
    }
};

namespace Bi
{
class Solution {
public:
    string longestDupSubstring(string s){
        string longest_str = "";
        string substring = "";
        bool is_match = false;
        int substr_len = 0;
        int j = 0;
        if(s.size() <= 1)
        {
            return "";
        }
        //unordered_set<string, StringHash, StringComparer> sub_set(4240);
        unordered_set<string> sub_set;
        int min_win_len = 1;
        int max_win_len = s.size() - 1;
        int mid_win_len = (max_win_len - min_win_len)/ 2 + min_win_len;
        for(; ;)   
        {
            //if(mid_win_len == min_win_len && max_win_len > min_win_len)
            //{
            //    ++mid_win_len;
            //}
            is_match = false;
            sub_set.clear();
            cout << min_win_len << ", " << max_win_len << ", mid_win_len: " << mid_win_len << endl;
            for(int i = 0; i + mid_win_len <= s.size(); ++ i)
            {
                substring = s.substr(i, mid_win_len);
                if(sub_set.find(substring) == sub_set.end())
                {
                    sub_set.insert(substring);
                }
                else
                {
                    longest_str = substring;
                    is_match = true;
                    break;
                }

            }
            if(mid_win_len == min_win_len)
            {
                break;
            }
            if(is_match)
            {
                min_win_len = mid_win_len + 1;
                mid_win_len = (max_win_len - min_win_len + 1)/ 2 + min_win_len;
            }
            else
            {
                max_win_len = mid_win_len - 1;
                mid_win_len = (max_win_len - min_win_len + 1)/ 2 + min_win_len;
            }
        }

        return longest_str;
    }
};
}
namespace Bi2
{
class Solution {
public:
    uint64_t proc_time = 0;
public:
    string longestDupSubstring(string s){
        string longest_str = "";
        string substring = "";
        bool is_match = false;
        int substr_len = 0;
        int j = 0;
        if(s.size() <= 1)
        {
            return "";
        }
        //unordered_set<string> sub_set(4240);
        set<pair<uint64_t, uint64_t>> sub_set;
        int min_win_len = 1;
        int max_win_len = s.size() - 1;
        int mid_win_len = (max_win_len - min_win_len)/ 2 + min_win_len;
        uint64_t t1 = 0;
        uint64_t t2 = 0;
        for(; ;)   
        {
            //if(mid_win_len == min_win_len && max_win_len > min_win_len)
            //{
            //    ++mid_win_len;
            //}
            is_match = false;
            sub_set.clear();
            //cout << min_win_len << ", " << max_win_len << ", mid_win_len: " << mid_win_len << endl;
            t1 = GetNowUsecs();
            int64_t last_hash_high_value = 0;
            int64_t last_hash_low_value = 0;
            int64_t last_begin_char = 0;
            //cout << endl << endl;
            for(int i = 0; i + mid_win_len <= s.size(); ++ i)
            {
                substring = s.substr(i, mid_win_len);
                if(i == 0)
                {
                    last_begin_char = (int64_t)(substring.at(0) - 'a') * pow(26, (mid_win_len - 1));
                    for(int m = 0; m < mid_win_len; ++m)
                    {
                        last_hash_low_value = (last_hash_low_value * 26) + (int64_t)(substring.at(m) - 'a');
                        last_hash_high_value +=  (int64_t)(last_hash_low_value / 100000000);
                        last_hash_low_value =    (int64_t)(last_hash_low_value % 100000000);
                    }
                    sub_set.insert(make_pair(last_hash_high_value, last_hash_low_value));
                }
                else
                {
                    //cout << "last_begin_char: " << last_begin_char << endl;
                    last_hash_low_value -= last_begin_char;
                    //cout << "last_begin_char after: " << last_hash_low_value << endl;
                    last_hash_low_value = last_hash_low_value * 26 + (int64_t)(substring.at(substring.size() - 1) - 'a');
                        last_hash_high_value +=  (int64_t)(last_hash_low_value / 100000000);
                        last_hash_low_value =    (int64_t)(last_hash_low_value % 100000000);
                    last_begin_char = (int64_t)(substring.at(0) - 'a') * pow(26, (mid_win_len - 1));
                    if(sub_set.find(make_pair(last_hash_high_value, last_hash_low_value)) == sub_set.end())
                    {
                        sub_set.insert(make_pair(last_hash_high_value, last_hash_low_value));
                    }
                    else
                    {
                        longest_str = substring;
                        is_match = true;
                //cout << substring << "(" << last_hash_high_value << "," << last_hash_low_value << ")" << endl;
                        break;
                    }
                }
                //cout << substring << "(" << last_hash_high_value << "," << last_hash_low_value << ")" << endl;
            }
            uint64_t t2 = GetNowUsecs();
            proc_time += t2 - t1;
            if(mid_win_len == min_win_len)
            {
                break;
            }
            if(is_match)
            {
                min_win_len = mid_win_len + 1;
                mid_win_len = (max_win_len - min_win_len + 1)/ 2 + min_win_len;
            }
            else
            {
                max_win_len = mid_win_len - 1;
                mid_win_len = (max_win_len - min_win_len + 1)/ 2 + min_win_len;
            }
        }

        return longest_str;
    }
};
}

int main()
{
    Bi2::Solution s;
    Bi::Solution s_bi;
    //string str = "banana";
    //string str = "uswlzarxlolqxrulrtsvroiyurnuyxnhayjogwrdyjwqndkbpdixvhneshkzcwhkpywlezetcijyuadbnjtccdowaanowbueroqdszwmpahxujfftjfjgobmktytaragofkxboannlnuohnbenvqhrrgivnhzpxdclltbtiknveitptiwiqhgjnsaxjgkkmsedwzftgyxdbkgwixgkskmdopdzkbrnzydeoapixrpbqlrnbdizjcylgcwgusvaogusefvigsovhrrlknacpdpeagkdjefrdpbfejulubxwlskrutbikwnvceulibpvlawcgtxuyfehkpygwjruadaahzjxggxtcyszyabxdypnogukfphmcclricytktofvfayeycrtvkvpqpedylhqfkkqlulqkuqxtvplctcxhyongrubkzeoopqxphqhjbmbpaawbzadurxeixzlbbwvhwusfwbaxxicapmxphiqewpwukfihacnyomethcjeiauvcqxyucdfzkxjehtdkinoklekpfliuyvjxhpcxvstqzwbpwdkakjnazbzpnhkmsrxvdmmrrjspzcbstwttgwybjpzknmzdpelpoeabfocymgqwsxzyswhdxqxgoyglgnqdvgmtgwfyyoeagpqtaimjfeeunptsrxwajksdbqposjpvgkatoojkxxyvpxhqxvhkqxaeojuqozaokynrljqpkatfthwxlrxyubeqkehsxvhrhwetkqhdvekxxwkprrydcqrbpgaspemjyrrtlvuvzxyioiyvzcsgljssqskgqwxhrdnblrrzfmbifmqjosxdkgvxgpzzhjatcgvmtkvrxswghbsawmqdddmgcwkgzqkmxuayaglnurwoaaifqoyytvyagvtcsbmdbbmnnndfkzdcahvqivdacvrntqikpdlwbvemqxxeyzohhxupexktowslnzolbayffdjkcsivykycoqbidipouxevjfvpyfhdudqtstjswzlwhmbccfjfuyagfyiimhejkbzjekpjaldujxqoungvxaegpumjkynxnfcemurxtaodpmlssdgovflprpkcbnebdkfozolhdqmmhdqlrgbysovzrglwfhvxiqhlpnbfdkwsyaouwtuwhgzfltbybnigunnaxeiwmqurqxlmickwiopejujcyyscdmcvlmmhdptninxdfqwppztivpnvjnaidcfudjfaagrgyuplqnjiicsiayrdbhsvsqoxyttovomvadkcddfiimpbyczccysfbgvefrouuhacijstanhtonrorhsxgfxjzcmhkqawucytsdebvtdbkufjakgacyyscuifqfdwckqxoddfbyvqxzjtgnlwuulhhqbltjehrcugaiifmuwpshwsndlpduhtaargbzamwfjxxfjbdaptkyxbwcisnnpbrqravxlgyxkaiohtxotfsrqiijccivuyjhuvzxdspdrqvjranshaksxprasngplvvmbzehudeersaoplloqghhygcshhjwibrjtxyvbwvbvviqquqgmytzywjnjhsdhudlqnycqrmqsxbtxxaekluncstselbalvvnghacilvzmardzvfqdxjhmmrslzzymwkvzixhvgulwimdfkaoslnyxfnanioafucprzkxpzzrdenbjhypalzgdhzkezejgpbevprsluquukymdbapevmuxbgcswjwwdrecmsuxccwonaeltscntzupapbaaywhfxkmquvtdbahewivliyqrohpervegyxlretyagmegtwdhvfsotnazgexgecnlaseijheotvozbngotvpwjgoehzmusviztwlgpvlfyusdlkoaqywhpimuvzkgkwwolfppxmmhwrokfnatztlzbzuedslubajohsbtudpjhuejdtcuujojhyeemtypcuuvumgkdudijwmygyiqpzpxayuxqdfanxhiookutfmtwpjahtirwgozfzwftbazrmiionqdpvsmjgwhvfjrbazsoqmfczueefzjhxseaszbolxkxieszftcvvmzicqbkpuvgpztfjtugarjdfewpiddlluhqbgityhjytbtuemfmssydpivbhvnlhhrcsumlrqeqgjhupkkrdtjhsgjqrpzbsbbkegvwxmbrtkeuejrlgwwbkirgrvqhddnazuocjpaajkbfcevwywkhqyypwcgosmvmpoysgatglbgbkbnscsemdcshxjyguxbnxfmslenyykiyskvknemlxzwdwrnwqbtruyqnuzqrwfrpdinooujtpefkxoeuykmrkexogocuvnokxasvhpbcavyeauraeqgdykyhtxgicxdemwszdzaeaesmdhnibxukmtmxgznfhwlojormocpxzykragnycqgcluccnabprjdgqodiisunbjbzwhvvcudoprgzagngfolnaybhtqrumaoxppiyesfzfysbgrnuprpimpkdtsscratomkqvpzlkdengrmttplielzyqrzpiaxscpqdnempzmkulenvbdcladybwmqkryryvemrvihvgwxkklwtzxsmiryebnkwszevuciehdxncxqgkhhhnnxtpcakghpyipjxuqbwqjznubyyjaowrctsvqzdcdopujgwyhtkadoiksxowebvopgopcsepgybxrilshqwwuzvkedfgcgjllrhichvuxyuxkeaqwqqmcjbragfrtipgualwddxfleddddmucsacnzmlzggdqpxqsdghtghnhvxrlvteqcjkluiggcbcmnatoweadbykzyepnhuewyxlbjpbxhmvefjzqglaotjvzxkdxozboldnjbwjirgavlxsudakqxyxfrzobehohdammwbzclnyxlhpmlpowvencvzzonnejvpvjtsljlgakohgfoswahjfaufpuphbtbgdbrefivaomlsqubvgmkdakrxaxteiwbggujydivouymdhsyccnvcbbflmoycuktzxcznxtawnhnnwomhyxdhduuppjffzuhbbvwkpjxfvnvobgtltqsggkjyiuciuxnokhrdcpsdezeqmemduqwgutasohydwcsosucvugemcgnyjiirbkxykzxbgbvxvsbcyfyraaspbyfhervypiywfmdbjewwnjhqyaihgrmmaucaxptyozifytdjdlwuackmuhhssnsppqjnlbjgajxtfyagliremtyxwvstzmzhdzfiikowtcohtasaifqwvuhibzjwjlcvgvvwcksiepfudxvummhevvvmfmvfxmpxjpedysczfbbckagpmvovmakeypzbhnnojdwsadsrvvjltlmokfdrduushtlxgqwnkacvuafjppxkboqtlysgcgnuiinuojfhbeqtfapkziovphakuprnummcsdkvhuizsyfqrycusamhsyiwrwbycnvaxmmvqmbjmfenlgtqpdzxjqgsonyuqeuxowyohybiohkudaguntdpuqbarbigriigzrpfvwoommqhnskcymvejyfsikugyqxdsknugpeckxqhktwrmflhpicubahcgspnkzuswvqrflsulqikjbjkmeoyqdkwxtnrqmutpnvkooglifsyjhevmavccesmihqyroluvyyxktzylwhnquxlgwglvlchedcasgrontsmkjurtshubefuwitpltihphrvvotyxgdgtsjysatkavvilykdgsytsifiliddvusfxdsiowhlxoxwbjhkemfneregnfcixywkkiytsuxnccybamneoaaasabzykyhxympthywwbqjgczykuyimagjxnczhdtxyiyymzjybcomwrzovsqhfdtoxpjpjmjvnyeeixtsrttxsvszssjpaqklaczvbjeyargimbympagsksrfhctrhyyomozolhrbvgzxtuvgbdabsyyfrkkdhrwscsitiksjuocmhvyuweoimuibgcuxgkpxjbfatqqczoqyumyrusqsxkwihwmhjedbpylikrkvikthctcgjgrjmppljvugmkwczgfstnqbylwimwqokgqhklcvyldqlzuspjxqjgqwzpqefzgcmoakicyheklekiqowlnupsknlykmnmheqzafqlkwuidhqarfmwfmncgoswvweutnjhdpjrdxzagdfqpjupbchaffboucrkwdtdmraclrgtyrfhszsfaaraaovkokhqwbwhgeyimifyebbupxujhhtmieiounacuxmxlmewyrmbcuxglzoxhnrvalgocgaqdpavikirbehgtlybziudmdlgsymegqktpergknqmpnwfzkbqacdvrujwhmdwfuczoobqtrwjyilypxrrenjchvirxwasuducuawymajnfnyxxtgpcgrdodqndamaaltcnmlfrwxsilhvgskjtfnmwnpodorjjpqpozrhyccksqnktchunbflujfldoqpftodvyaccbdwxhzzihzqrgigqloosobrpnjvruouqpmtmksmlupjihjpqrncvjuascdwazepynhfeehrwgyxjdgybegdajuwzjhgrzvkpshpsqeoxhdfnhnwbuhsaoyumeunyznabqtwqbkyqooyzajtemzhoertrzvkfjjxfhddaqyvqvrqltzwtgkdlvpowhnyfdtcfwazxuaamguczphwqwznjhvbgzzmpxybfwdezclmecbojukvrmaxruvxmshdtcsjohzgpoqohlcnpoxvklsmmoetyvfebenroejsdgbvrxnuswsnejgwuolsdqzpbogynqvodsnbccffpnnblycziedwloxidhjlbpvdxzpsgqxmvynrcjleyldvepwtpvmnroebilexnnfebqrctrbeggirnigxauyxmfdyumngsdcexzqwgyhneeyshjfpxyvelhmdgqvjnwsnuuorkwbvrnzfqxgaihsktkxregdiungexuoqaikcioohsricytddadbjkbpuvprbzmxbpxwzdgaotwpinrdfebymilllpttfebctlnrhpxdnyyczkqesdrgauysgutcmushvkdsncpwdovzyhmqxnyxzxgilzmprmltduvmbjizazgctilvpnosumbanzxqrewrhncoxvrwttdgpblnbxdwkgevhguuxmulxrqalfqcttfgjtmvtfckwkqzhidabfavaqphvlfwtytilvunzdnxisqarzbnrpuhlsjlqbcdtgioioopisesfrbslyqpwkftdbyrfgyigaappfghswzksifhrwbfixytdyuaqylsgmseptwjaqmpompzeqactkgsygalrwpdzankvcuxufrsmmnoinhdjwqcywtkgpuxzjanpiooorghszsptudnokiidqhgxmqekhuoupurwnorcnjrtsjiqyvrpjxitufmsilrwlkxnuagljvvflmudqkdqqlzvyklpizafwzjpmvburpjdvgcousfceynkzkeggpsswefwhmsttpjdlbqptmojyblxbmgzjqmotnhsmortjnhyeerrsiaosqnaxhovxxojuoctbvjvcnlfxyjvpfzddhcpkimtkhztfsagrleovjzwnfrnwzxtsrewjmrfvqenalooplzjicozoyyecvhzfrargwqljhjknvefhfnxmyssimyvcmguqdhmsxkshhvuobenlgmfpnaoskdzihlrhvfyoekdujmrkgeyrpgdkqbfulqggvzboxbpgnvxparetxgjgyiztpgbklsbclmhahtvnkqugqjuerliyuvvhbecrgktbznsnxmaebjkbwhbnqirvkzzdtdoynbrnxqbivafzszibpduxiebotuphnipiadqulgvowfpqhstysawzdftziymukygmrtdlftivuoburfyyexngsjjlcwnqdbjlpaaseixlwraarkenojbjhqxkwzyvetyeogdqjyifjlqczlajcrlcmoslaowfagpbnyckdlmwrfohsukaixmgrkqjebrkljwiwktslbdawgfjrqzzmnrwbuygeamkdxutaabkdvavbuwzebghzxlciislnwyowludkjtxikxdadkkixxbtabxnzlobnoyadbnjomksddvgjrcfudwazrzptkkryqgovlciweuprrohotowkdupbazyocsanlhprydovbqwweeseorekcxaxxmuqgemnctycjchiuwetbycqzwygmdewujaldjogtsdwugmszyysysuygvadwshotmwlytemrcvsazmamqzijupkldjknndjxnpirulgrzzexloiucxwfqbbsdmlhujkmnxzaqqrrmtjywkkuwsqokhzeznzybandlsbwcoaiibsfufnvjqbrzggqfrvzpiaewtpfiencojahcljdubuqmwzxvlnwcewzgtrbvxxilnyqdscrmvavdmxotnppwwzilanwuxyibsfrarmxjexouwfvidgdyzaletybcwhwqhvrzhggfhfyeekfthinqlnfkzlerwedbnbotwoxxtjwkvmfliubretmvjvnmxvcjjcdwmmecrixhivokbnouzsdtratejqmazncvodkooecbnxgiuvqamhidiytynowdoktjfuihyvkjnjngtelyaytuoolpevjknpejejoxzoersmzkfdxnfyduylzedmkozsylcxheohpwjcdvyrhejnawvauzwwufatqkmundusufxvudfottxyhokmpfkjqxwbivsyppmtlcbdpgqeaszzgclaerigzldbtprxjyeixgquashtpokiyblarydsplvadcagmfttwbuslstlryztyljvdpcmzdufddneklbzjdbxvcflhmihslhjxsnysmuzjnbiwccvikgbndpdcymrvdubpwvnxnfxyazdnvmlhaisrbkpvaqhtleiezbbzfbbtugkrgocqzqnaeogzqjrrukvtkkejsmmqticbueuxxgwfxrljwykqjjcbbdypeihcbhspguiluyunyhjdolxhpwcawxofreizvbqvlykkmsutyzerbandsijhcpzllphpldxsovybcezefgzyoxlnqzypavpdoehqatqtokstkkneqyqcpggysvidzujuqvmfdyfhdsvemqaozxifackqqfavizltygghapbqataolckbineefqrunvdqwigzvjiwbujknolhbcxfgfqbcjgddlsvnzbfflgbfhbennlonoosuleuolyhrsgryiefmvitbfcnqkvyckfcpwistwcflpsqqpfpedioinrlkxgsbfzhtxtjzfdjypjjfkuqfplsghtjcqwukfxdmbsaxoezwctuvjnvrldlzrngmgbhsuqldyxaoimomtpipnpekcpqmgslkhoddkwdqimfqkgazfrdwkcyvqnigdikqzsfgvmlyyjnpaavmmnjfxipfcwuipcxfpebourxbsovfvwdwtdxdispbzuzbzwyjpskaamanirxbqnntrjjnjnkdonxbjofwpruxfggxfocvjvdaapflptpwmuujlidipagdudwqoqorspwqoeupounquwingejjhbxwwqgcbzfmodlvpptsqjoqliopitivbrxfpqqzrjppftuvyxieymksrrebzalipyweobgmpzazrzigsmxmdsxbrwewungjuspckdtclcseeqfutzelhelyjnnitviwksblwgyjvyildeivmymlwqsvkueecfdffoavnspdgeuqivkizubcxfucbrgiymxyjrpdumfyvrvqakkzsknsfrnurdavxoquncgppcahxrwdsbvzhhsxtdwadrcjexcnamhesnskazwkzslujboubzueoqgxiawjquqsavycnyptutqfhdflpjvlkkaufypqbkfkqlkuakuvotpxdmrsrscatmxgkiwlkxqactfikzbqmeljhhlpycgikltdifkguvnklufmlmymwmgnivnzqolwcyyqgmufcdfxomwfhykyvjsjtrwbwfprcowifemayhclmhfhdmacjdjbjbmupqwmcnatovvfxodiqwzrkwfzabhfkcknncirmjcqudafaqizduwzbtblqzxxwzzsvcvatilvcbpljrwyfbexmvnejtycgjymajunvlgbizcxbgeigcvcprhmuhlejpzyyhvjcwiuqbdagbqbqzfhvgzeyivksbpxmhqvtncynsyzgeknjrrhgcfnhihumgxbzrefzgbvaxvxhedzvdzebmxdzgzifyfyyfcluccaxzmbylktrprawebqgmukxgtlouwcruomaogosltkvevyolusgitgqyqcbryhxwtonkyehpctiqwvdatpfzljwwtlnxrbqdssalqnhefzaoebzmrbardwbmsfoxcsgnajyruawypwqtqxwfrhqwsusyrckghuqjciofzfcfsddrvnkhjhmmtsqpiimkobwlhdmsinglfwuutcepcoianuudwrdeikmukrdajzsymarepqbvuqcjegwyharjqphmnibwzucoxsezkvgownrcgjsmttquiahqvywdftsmpvyofbwntkgkfplxnetgmdfawjkpaigitkfveurgwzjsgwuynilnmbmdzawsrbtetpmtipqpalvatzhaihvrjvmseyuvpowzvnsdekkgbdcngnjykryoiqyeecbooghnridvykantprptapkidkpgdqvoafthbupeglxlumyyxwykgvbjcamwqwbkjluqynygybwztbqraafrarrpfodreeeykixkgrolgqjdcqc";
    string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    //string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //string str = "abcd";
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //string str = "nnpxouomcofdjuujloanjimymadkuepightrfodmauhrsy";
    //string str = "polxtvqlurgobbzbjcjsupskvzmtuveuavrzcxaifmdwqjbuejdasuxcvsupqnucorfawncjqkbakilhiekavhmsjbtlsfydijafxhgrgbsswtnvdquwokcliaxevairergwdtndsibiulqiutkcwsqpzuyypnhiowgvkkdbpkoyvgwyuqcokjnxluamwnuhqjtaossezwxvkpdkqcleqjkelcludtbigxkueupnxjncrbgvdrsdpppqqcopnwadqsxkvlkghfmtvdeygpyxamvxhmmaunxskgnenobvnzizbxwrjeedisrgzykoaidiffzqzsmirxkvfwmtifywamcpxziyjohcudzelgbmdgiaqwnzdbkwbhdioiokaivzlzscshrvbmggdztjuimribrgmdlcctvldbcxwpqnqbkzrcayqdqraobqcgoxxocclasphcjcydpkgkqhrmmxtklpxfxnrgnzczjxanaltnjhwfatgryqhcllemgqcchiagizpdgiqioqyhrpattutmuotrcwtxvdqzzsomofizebbqrgwruydyawsssjkakjpjlzmfhmjetymftxrhilpcgfqyoohyydnodfortlkeoncmfkdraiqydxcodyapjaxumjwczwmthrcecfgsswwtnyqurvggamjbsjdzmcuyefwnsrnhhpusfdsxbsrsrywbccullupdbovnmzluqsfdhqbef";
    //string str = "abcd";
    //string str = "djpqwlrroqeuwwqgxnvdftzgsgnmpnhnhezixyhlydjjekpeczwtguowubfjsyohxaihmbjzfchmbnppouguvklmiaqkgomqzvvfubklwexbnzbdkvtxjnpzmfdgomvvsekluemjqaatkbhklusgxbezjghoddwcmirwrnnsgzjzwrnfyqgjylzgwhwipinohhzkywikevsqurnirnmmkgwpgvdswttwpingslbzxzsodqvlluqetfzfzbdhilaugrxewhomtwzjyldxzwtxmufbcrxtqfpcqscbbstplqczhumhedcmmgfkhdyetexcyrlvdrkgxzsncrpoomtqwnwozbteedjozikggwkbexbibruqdpekpjpzzymxpvtsderhjwxvyfahximykcndxskcjwewnfcbvymijwkrisjtzyiegysxpyfdrblxjquytzgvajmdvylemhqcctivjzmkdojbpvucgswycfnjkyoqvzlufphsrvhcbkxamqmaoveycykirpboguhrimemgkkbdmkyvalkpmktlkhwtaafuphdksucgianjkyztzyrndfjhkemdlgnmbucmqqyvjmzqlmgerhvzdtbjsagisjsqnrzqlmimtxumlngktcptgpcevpybghuycisxbemgpwptokdqvzp";
    uint64_t t1 = GetNowUsecs();
    string longeststr = s.longestDupSubstring(str);
    uint64_t t2 = GetNowUsecs();
    cout << "Spend time: " << (t2 - t1) << endl;
    cout << longeststr << endl;

    cout << "===== Bi ======" << endl;
    t1 = GetNowUsecs();
    string longeststr_bi = s_bi.longestDupSubstring(str);
    t2 = GetNowUsecs();
    //cout << "Procc time: " << s_bi.proc_time << endl;
    cout << "Spend time: " << (t2 - t1) << endl;
    cout << longeststr_bi << endl;
    cout << "Equal? " << (longeststr == longeststr_bi) << endl;
    return 0;
}
