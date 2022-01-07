/*
   https://leetcode-cn.com/problems/longest-duplicate-substring/
   */
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <utility>
#include <cmath>
#include <climits>
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
            //cout << min_win_len << ", " << max_win_len << ", mid_win_len: " << mid_win_len << endl;
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
    const int64_t mod_num  = 10000000000LL;
    unordered_map<pair<int32_t , int32_t >,  pair<int64_t, int64_t>, PairHash, PairComparer> pow_cache;
    //char buf[1024] = "";
    //char res_buf[1024] = "";
    uint64_t proc_time = 0;
public:
    pair<int64_t, int64_t> my_pow(int32_t x, int32_t y)
    {
#if 1
        uint64_t t1 = GetNowUsecs();
        auto iter = pow_cache.find(make_pair(x, y));
         pair<int64_t, int64_t> tmp_pair;
        if(iter != pow_cache.end())
        {
            //cout << "(" << x << ", " << y << ")" << iter->second.first << ", " << iter->second.second << endl;
            tmp_pair =  iter->second;
        }
        else if(y == 1)
        {
            tmp_pair = make_pair(0LL, (int64_t)x);
            pow_cache.insert(make_pair(make_pair(x, y), tmp_pair));
        }
        else if(y <= 0)
        {
            tmp_pair = make_pair(0LL, 1LL);
            pow_cache.insert(make_pair(make_pair(x, y), tmp_pair));
        }
        else
        {
            tmp_pair = num_mul(my_pow(x, y - 1), x, 1); 
            pow_cache.insert(make_pair(make_pair(x, y), tmp_pair));
        }
        uint64_t t2 = GetNowUsecs();
        cout << (t2 - t1) << endl;
        proc_time += (t2 - t1);
        return tmp_pair;
#else
        int low = 1;
        int high = 0;
        for(int i = 0; i < y; ++i)
        {
            low = low * x;
            if(low > mod_num)
            {
            high += (int64_t)(low / mod_num);
            low = low % mod_num;
            }
            //if(high < 0 || low < 0)
                //cout << "x,y: " << x << ", " << y << " => " << "(" << high << ", " << low <<  ")" << endl;
        }
        auto tmp_pair = make_pair(high, low);
        pow_cache.insert(make_pair(make_pair(x, y), tmp_pair));
        return tmp_pair;
#endif
    }
    void num_sub(pair<int64_t, int64_t> &pair_num, const pair<int64_t, int64_t>& mul_pair_num)
    {
        //snprintf(buf, sizeof(buf), "(%lld, %lld) - (%lld, %lld) = ", pair_num.first, pair_num.second, mul_pair_num.first, mul_pair_num.second);
        if(pair_num.second < mul_pair_num.second) 
        {
            pair_num.second += mod_num;
            pair_num.first -= 1;
        }
        pair_num.second -= mul_pair_num.second;
        pair_num.first -= mul_pair_num.first;
        //snprintf(res_buf, sizeof(res_buf), "(%lld, %lld)", pair_num.first, pair_num.second);
        //cout << buf << res_buf << endl;
        return;
    }
    void num_add(pair<int64_t, int64_t> &pair_num, const pair<int64_t, int64_t>& add_pair_num)
    {
        //snprintf(buf, sizeof(buf), "(%lld, %lld) + (%lld, %lld) = ", pair_num.first, pair_num.second, add_pair_num.first, add_pair_num.second);
        pair_num.second += add_pair_num.second;
        pair_num.first += add_pair_num.first;
        if(pair_num.second > mod_num)
        {
            pair_num.first += (int64_t)(pair_num.second / mod_num);
            pair_num.second = (int64_t)(pair_num.second % mod_num);
            pair_num.first = (int64_t)(pair_num.first / mod_num);
        }
        //snprintf(res_buf, sizeof(res_buf), "(%lld, %lld)", pair_num.first, pair_num.second);
        //cout << buf << res_buf << endl;
        return;
    }
    void num_mul(pair<int64_t, int64_t> &pair_num, int64_t num)
    {
        //snprintf(buf, sizeof(buf), "(%lld, %lld) * %lld = ", pair_num.first, pair_num.second, num);
        pair_num.second = pair_num.second * num;
        pair_num.first = pair_num.first * num;

        if(pair_num.second > mod_num || pair_num.first > mod_num)
        {
        pair_num.first += (int64_t)(pair_num.second / mod_num);
        pair_num.second = (int64_t)(pair_num.second % mod_num);
        pair_num.first = (int64_t)(pair_num.first % mod_num);
        }
        //snprintf(res_buf, sizeof(res_buf), "(%lld, %lld)", pair_num.first, pair_num.second);
        //cout << buf << res_buf << endl;
        return;
    }
    pair<int64_t, int64_t> num_mul(pair<int64_t, int64_t> &&tmp_pair_num, int64_t num, int32_t)
    {
        //snprintf(buf, sizeof(buf), "(%lld, %lld) * %lld = ", pair_num.first, pair_num.second, num);
        pair<int64_t, int64_t> pair_num = tmp_pair_num;
        pair_num.second = pair_num.second * num;
        pair_num.first = pair_num.first * num;

        if(pair_num.second > mod_num || pair_num.first > mod_num)
        {
        pair_num.first += (int64_t)(pair_num.second / mod_num);
        pair_num.second = (int64_t)(pair_num.second % mod_num);
        pair_num.first = (int64_t)(pair_num.first % mod_num);
        }
        //snprintf(res_buf, sizeof(res_buf), "(%lld, %lld)", pair_num.first, pair_num.second);
        //cout << buf << res_buf << endl;
        return pair_num;
    }
public:
    string longestDupSubstring(string s){
        string longest_str = "";
        string org_str = s;
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
            //        high     low
        std::pair<int64_t, int64_t> last_hash = std::make_pair(0LL, 0LL);
            std::pair<int64_t, int64_t> last_begin_char_hash = std::make_pair(0LL, 0LL);
            std::pair<int64_t, int64_t> tmp_pair = std::make_pair(0LL, 0LL);

        char * p_str = new char[s.size() + 1];
        strncpy(p_str, s.c_str(), s.size() + 1); 
        //cout << s << endl;
        for(int i = 0; i < s.size(); ++i)
        {
            p_str[i] = (p_str[i] - 'a');
        }
        s = string(p_str, s.size());
        //cout << s << endl;
        for(; ;)   
        {
            is_match = false;
            sub_set.clear();

            last_hash.first = 0LL;
            last_hash.second = 0LL;

            last_begin_char_hash.first = 0LL;
            last_begin_char_hash.second = 0LL;
            
        
            for(int i = 0; i + mid_win_len <= s.size(); ++ i)
            {
                substring = s.substr(i, mid_win_len);
                if(i == 0)
                {
                    //cout << substring.at(0) - 'a' << endl;
                    last_begin_char_hash = my_pow(26, (mid_win_len - 1));
                    //num_mul(last_begin_char_hash, (int64_t)(substring.at(0) - 'a'));
                    num_mul(last_begin_char_hash, (int64_t)(substring.at(0)));

                    for(int m = 0; m < mid_win_len; ++m)
                    {
                        num_mul(last_hash, 26);
                        tmp_pair.first = 0LL;
                        tmp_pair.second = (int64_t)(substring.at(m));
                        //tmp_pair.second = (int64_t)(substring.at(m) - 'a');
                        num_add(last_hash, tmp_pair);
                        //num_add(last_hash, make_pair(0LL, (int64_t)(substring.at(m) - 'a')));
                    }
                //cout << substring << "(" << last_hash.first << "," << last_hash.second << ")" << endl;
                    sub_set.insert(last_hash);
                }
                else
                {
                    //cout << "last_begin_char: " << last_begin_char << endl;
                    //cout << "last_begin_char after: " << last_begin_char << " => " << last_hash_low_value << endl;
                    num_sub(last_hash, last_begin_char_hash);
                    num_mul(last_hash, 26LL);

                    tmp_pair.first = 0LL;
                    tmp_pair.second = (int64_t)(substring.at(substring.size() - 1));
                    //tmp_pair.second = (int64_t)(substring.at(substring.size() - 1) - 'a');
                    num_add(last_hash, tmp_pair);
                    //num_add(last_hash, make_pair(0LL, (int64_t)(substring.at(substring.size() - 1) - 'a')));

                    last_begin_char_hash = my_pow(26, (mid_win_len - 1));
                    num_mul(last_begin_char_hash, (int64_t)(substring.at(0)));
                    //num_mul(last_begin_char_hash, (int64_t)(substring.at(0) - 'a'));
                //cout << substring << " => " << substring.at(0) << " (" << last_begin_char_hash.first << "," << last_begin_char_hash.second << ")" << endl;
                    if(sub_set.find(last_hash) == sub_set.end())
                    {
                        sub_set.insert(last_hash);
                    }
                    else
                    {
                        longest_str = org_str.substr(i, mid_win_len);
                        is_match = true;
                    //cout << "[Result  ]" << substring.size() << substring << "(" << last_hash.first << "," << last_hash.second << ")" << endl;
                        break;
                    }
                }
                //cout <<  "[Result1]" << substring.size() << "(" << last_hash.first << "," << last_hash.second << ")" << endl;
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

int main()
{
    Bi2::Solution s;
    Bi::Solution s_bi;
    //string str = "banana";
    string str = "uswlzarxlolqxrulrtsvroiyurnuyxnhayjogwrdyjwqndkbpdixvhneshkzcwhkpywlezetcijyuadbnjtccdowaanowbueroqdszwmpahxujfftjfjgobmktytaragofkxboannlnuohnbenvqhrrgivnhzpxdclltbtiknveitptiwiqhgjnsaxjgkkmsedwzftgyxdbkgwixgkskmdopdzkbrnzydeoapixrpbqlrnbdizjcylgcwgusvaogusefvigsovhrrlknacpdpeagkdjefrdpbfejulubxwlskrutbikwnvceulibpvlawcgtxuyfehkpygwjruadaahzjxggxtcyszyabxdypnogukfphmcclricytktofvfayeycrtvkvpqpedylhqfkkqlulqkuqxtvplctcxhyongrubkzeoopqxphqhjbmbpaawbzadurxeixzlbbwvhwusfwbaxxicapmxphiqewpwukfihacnyomethcjeiauvcqxyucdfzkxjehtdkinoklekpfliuyvjxhpcxvstqzwbpwdkakjnazbzpnhkmsrxvdmmrrjspzcbstwttgwybjpzknmzdpelpoeabfocymgqwsxzyswhdxqxgoyglgnqdvgmtgwfyyoeagpqtaimjfeeunptsrxwajksdbqposjpvgkatoojkxxyvpxhqxvhkqxaeojuqozaokynrljqpkatfthwxlrxyubeqkehsxvhrhwetkqhdvekxxwkprrydcqrbpgaspemjyrrtlvuvzxyioiyvzcsgljssqskgqwxhrdnblrrzfmbifmqjosxdkgvxgpzzhjatcgvmtkvrxswghbsawmqdddmgcwkgzqkmxuayaglnurwoaaifqoyytvyagvtcsbmdbbmnnndfkzdcahvqivdacvrntqikpdlwbvemqxxeyzohhxupexktowslnzolbayffdjkcsivykycoqbidipouxevjfvpyfhdudqtstjswzlwhmbccfjfuyagfyiimhejkbzjekpjaldujxqoungvxaegpumjkynxnfcemurxtaodpmlssdgovflprpkcbnebdkfozolhdqmmhdqlrgbysovzrglwfhvxiqhlpnbfdkwsyaouwtuwhgzfltbybnigunnaxeiwmqurqxlmickwiopejujcyyscdmcvlmmhdptninxdfqwppztivpnvjnaidcfudjfaagrgyuplqnjiicsiayrdbhsvsqoxyttovomvadkcddfiimpbyczccysfbgvefrouuhacijstanhtonrorhsxgfxjzcmhkqawucytsdebvtdbkufjakgacyyscuifqfdwckqxoddfbyvqxzjtgnlwuulhhqbltjehrcugaiifmuwpshwsndlpduhtaargbzamwfjxxfjbdaptkyxbwcisnnpbrqravxlgyxkaiohtxotfsrqiijccivuyjhuvzxdspdrqvjranshaksxprasngplvvmbzehudeersaoplloqghhygcshhjwibrjtxyvbwvbvviqquqgmytzywjnjhsdhudlqnycqrmqsxbtxxaekluncstselbalvvnghacilvzmardzvfqdxjhmmrslzzymwkvzixhvgulwimdfkaoslnyxfnanioafucprzkxpzzrdenbjhypalzgdhzkezejgpbevprsluquukymdbapevmuxbgcswjwwdrecmsuxccwonaeltscntzupapbaaywhfxkmquvtdbahewivliyqrohpervegyxlretyagmegtwdhvfsotnazgexgecnlaseijheotvozbngotvpwjgoehzmusviztwlgpvlfyusdlkoaqywhpimuvzkgkwwolfppxmmhwrokfnatztlzbzuedslubajohsbtudpjhuejdtcuujojhyeemtypcuuvumgkdudijwmygyiqpzpxayuxqdfanxhiookutfmtwpjahtirwgozfzwftbazrmiionqdpvsmjgwhvfjrbazsoqmfczueefzjhxseaszbolxkxieszftcvvmzicqbkpuvgpztfjtugarjdfewpiddlluhqbgityhjytbtuemfmssydpivbhvnlhhrcsumlrqeqgjhupkkrdtjhsgjqrpzbsbbkegvwxmbrtkeuejrlgwwbkirgrvqhddnazuocjpaajkbfcevwywkhqyypwcgosmvmpoysgatglbgbkbnscsemdcshxjyguxbnxfmslenyykiyskvknemlxzwdwrnwqbtruyqnuzqrwfrpdinooujtpefkxoeuykmrkexogocuvnokxasvhpbcavyeauraeqgdykyhtxgicxdemwszdzaeaesmdhnibxukmtmxgznfhwlojormocpxzykragnycqgcluccnabprjdgqodiisunbjbzwhvvcudoprgzagngfolnaybhtqrumaoxppiyesfzfysbgrnuprpimpkdtsscratomkqvpzlkdengrmttplielzyqrzpiaxscpqdnempzmkulenvbdcladybwmqkryryvemrvihvgwxkklwtzxsmiryebnkwszevuciehdxncxqgkhhhnnxtpcakghpyipjxuqbwqjznubyyjaowrctsvqzdcdopujgwyhtkadoiksxowebvopgopcsepgybxrilshqwwuzvkedfgcgjllrhichvuxyuxkeaqwqqmcjbragfrtipgualwddxfleddddmucsacnzmlzggdqpxqsdghtghnhvxrlvteqcjkluiggcbcmnatoweadbykzyepnhuewyxlbjpbxhmvefjzqglaotjvzxkdxozboldnjbwjirgavlxsudakqxyxfrzobehohdammwbzclnyxlhpmlpowvencvzzonnejvpvjtsljlgakohgfoswahjfaufpuphbtbgdbrefivaomlsqubvgmkdakrxaxteiwbggujydivouymdhsyccnvcbbflmoycuktzxcznxtawnhnnwomhyxdhduuppjffzuhbbvwkpjxfvnvobgtltqsggkjyiuciuxnokhrdcpsdezeqmemduqwgutasohydwcsosucvugemcgnyjiirbkxykzxbgbvxvsbcyfyraaspbyfhervypiywfmdbjewwnjhqyaihgrmmaucaxptyozifytdjdlwuackmuhhssnsppqjnlbjgajxtfyagliremtyxwvstzmzhdzfiikowtcohtasaifqwvuhibzjwjlcvgvvwcksiepfudxvummhevvvmfmvfxmpxjpedysczfbbckagpmvovmakeypzbhnnojdwsadsrvvjltlmokfdrduushtlxgqwnkacvuafjppxkboqtlysgcgnuiinuojfhbeqtfapkziovphakuprnummcsdkvhuizsyfqrycusamhsyiwrwbycnvaxmmvqmbjmfenlgtqpdzxjqgsonyuqeuxowyohybiohkudaguntdpuqbarbigriigzrpfvwoommqhnskcymvejyfsikugyqxdsknugpeckxqhktwrmflhpicubahcgspnkzuswvqrflsulqikjbjkmeoyqdkwxtnrqmutpnvkooglifsyjhevmavccesmihqyroluvyyxktzylwhnquxlgwglvlchedcasgrontsmkjurtshubefuwitpltihphrvvotyxgdgtsjysatkavvilykdgsytsifiliddvusfxdsiowhlxoxwbjhkemfneregnfcixywkkiytsuxnccybamneoaaasabzykyhxympthywwbqjgczykuyimagjxnczhdtxyiyymzjybcomwrzovsqhfdtoxpjpjmjvnyeeixtsrttxsvszssjpaqklaczvbjeyargimbympagsksrfhctrhyyomozolhrbvgzxtuvgbdabsyyfrkkdhrwscsitiksjuocmhvyuweoimuibgcuxgkpxjbfatqqczoqyumyrusqsxkwihwmhjedbpylikrkvikthctcgjgrjmppljvugmkwczgfstnqbylwimwqokgqhklcvyldqlzuspjxqjgqwzpqefzgcmoakicyheklekiqowlnupsknlykmnmheqzafqlkwuidhqarfmwfmncgoswvweutnjhdpjrdxzagdfqpjupbchaffboucrkwdtdmraclrgtyrfhszsfaaraaovkokhqwbwhgeyimifyebbupxujhhtmieiounacuxmxlmewyrmbcuxglzoxhnrvalgocgaqdpavikirbehgtlybziudmdlgsymegqktpergknqmpnwfzkbqacdvrujwhmdwfuczoobqtrwjyilypxrrenjchvirxwasuducuawymajnfnyxxtgpcgrdodqndamaaltcnmlfrwxsilhvgskjtfnmwnpodorjjpqpozrhyccksqnktchunbflujfldoqpftodvyaccbdwxhzzihzqrgigqloosobrpnjvruouqpmtmksmlupjihjpqrncvjuascdwazepynhfeehrwgyxjdgybegdajuwzjhgrzvkpshpsqeoxhdfnhnwbuhsaoyumeunyznabqtwqbkyqooyzajtemzhoertrzvkfjjxfhddaqyvqvrqltzwtgkdlvpowhnyfdtcfwazxuaamguczphwqwznjhvbgzzmpxybfwdezclmecbojukvrmaxruvxmshdtcsjohzgpoqohlcnpoxvklsmmoetyvfebenroejsdgbvrxnuswsnejgwuolsdqzpbogynqvodsnbccffpnnblycziedwloxidhjlbpvdxzpsgqxmvynrcjleyldvepwtpvmnroebilexnnfebqrctrbeggirnigxauyxmfdyumngsdcexzqwgyhneeyshjfpxyvelhmdgqvjnwsnuuorkwbvrnzfqxgaihsktkxregdiungexuoqaikcioohsricytddadbjkbpuvprbzmxbpxwzdgaotwpinrdfebymilllpttfebctlnrhpxdnyyczkqesdrgauysgutcmushvkdsncpwdovzyhmqxnyxzxgilzmprmltduvmbjizazgctilvpnosumbanzxqrewrhncoxvrwttdgpblnbxdwkgevhguuxmulxrqalfqcttfgjtmvtfckwkqzhidabfavaqphvlfwtytilvunzdnxisqarzbnrpuhlsjlqbcdtgioioopisesfrbslyqpwkftdbyrfgyigaappfghswzksifhrwbfixytdyuaqylsgmseptwjaqmpompzeqactkgsygalrwpdzankvcuxufrsmmnoinhdjwqcywtkgpuxzjanpiooorghszsptudnokiidqhgxmqekhuoupurwnorcnjrtsjiqyvrpjxitufmsilrwlkxnuagljvvflmudqkdqqlzvyklpizafwzjpmvburpjdvgcousfceynkzkeggpsswefwhmsttpjdlbqptmojyblxbmgzjqmotnhsmortjnhyeerrsiaosqnaxhovxxojuoctbvjvcnlfxyjvpfzddhcpkimtkhztfsagrleovjzwnfrnwzxtsrewjmrfvqenalooplzjicozoyyecvhzfrargwqljhjknvefhfnxmyssimyvcmguqdhmsxkshhvuobenlgmfpnaoskdzihlrhvfyoekdujmrkgeyrpgdkqbfulqggvzboxbpgnvxparetxgjgyiztpgbklsbclmhahtvnkqugqjuerliyuvvhbecrgktbznsnxmaebjkbwhbnqirvkzzdtdoynbrnxqbivafzszibpduxiebotuphnipiadqulgvowfpqhstysawzdftziymukygmrtdlftivuoburfyyexngsjjlcwnqdbjlpaaseixlwraarkenojbjhqxkwzyvetyeogdqjyifjlqczlajcrlcmoslaowfagpbnyckdlmwrfohsukaixmgrkqjebrkljwiwktslbdawgfjrqzzmnrwbuygeamkdxutaabkdvavbuwzebghzxlciislnwyowludkjtxikxdadkkixxbtabxnzlobnoyadbnjomksddvgjrcfudwazrzptkkryqgovlciweuprrohotowkdupbazyocsanlhprydovbqwweeseorekcxaxxmuqgemnctycjchiuwetbycqzwygmdewujaldjogtsdwugmszyysysuygvadwshotmwlytemrcvsazmamqzijupkldjknndjxnpirulgrzzexloiucxwfqbbsdmlhujkmnxzaqqrrmtjywkkuwsqokhzeznzybandlsbwcoaiibsfufnvjqbrzggqfrvzpiaewtpfiencojahcljdubuqmwzxvlnwcewzgtrbvxxilnyqdscrmvavdmxotnppwwzilanwuxyibsfrarmxjexouwfvidgdyzaletybcwhwqhvrzhggfhfyeekfthinqlnfkzlerwedbnbotwoxxtjwkvmfliubretmvjvnmxvcjjcdwmmecrixhivokbnouzsdtratejqmazncvodkooecbnxgiuvqamhidiytynowdoktjfuihyvkjnjngtelyaytuoolpevjknpejejoxzoersmzkfdxnfyduylzedmkozsylcxheohpwjcdvyrhejnawvauzwwufatqkmundusufxvudfottxyhokmpfkjqxwbivsyppmtlcbdpgqeaszzgclaerigzldbtprxjyeixgquashtpokiyblarydsplvadcagmfttwbuslstlryztyljvdpcmzdufddneklbzjdbxvcflhmihslhjxsnysmuzjnbiwccvikgbndpdcymrvdubpwvnxnfxyazdnvmlhaisrbkpvaqhtleiezbbzfbbtugkrgocqzqnaeogzqjrrukvtkkejsmmqticbueuxxgwfxrljwykqjjcbbdypeihcbhspguiluyunyhjdolxhpwcawxofreizvbqvlykkmsutyzerbandsijhcpzllphpldxsovybcezefgzyoxlnqzypavpdoehqatqtokstkkneqyqcpggysvidzujuqvmfdyfhdsvemqaozxifackqqfavizltygghapbqataolckbineefqrunvdqwigzvjiwbujknolhbcxfgfqbcjgddlsvnzbfflgbfhbennlonoosuleuolyhrsgryiefmvitbfcnqkvyckfcpwistwcflpsqqpfpedioinrlkxgsbfzhtxtjzfdjypjjfkuqfplsghtjcqwukfxdmbsaxoezwctuvjnvrldlzrngmgbhsuqldyxaoimomtpipnpekcpqmgslkhoddkwdqimfqkgazfrdwkcyvqnigdikqzsfgvmlyyjnpaavmmnjfxipfcwuipcxfpebourxbsovfvwdwtdxdispbzuzbzwyjpskaamanirxbqnntrjjnjnkdonxbjofwpruxfggxfocvjvdaapflptpwmuujlidipagdudwqoqorspwqoeupounquwingejjhbxwwqgcbzfmodlvpptsqjoqliopitivbrxfpqqzrjppftuvyxieymksrrebzalipyweobgmpzazrzigsmxmdsxbrwewungjuspckdtclcseeqfutzelhelyjnnitviwksblwgyjvyildeivmymlwqsvkueecfdffoavnspdgeuqivkizubcxfucbrgiymxyjrpdumfyvrvqakkzsknsfrnurdavxoquncgppcahxrwdsbvzhhsxtdwadrcjexcnamhesnskazwkzslujboubzueoqgxiawjquqsavycnyptutqfhdflpjvlkkaufypqbkfkqlkuakuvotpxdmrsrscatmxgkiwlkxqactfikzbqmeljhhlpycgikltdifkguvnklufmlmymwmgnivnzqolwcyyqgmufcdfxomwfhykyvjsjtrwbwfprcowifemayhclmhfhdmacjdjbjbmupqwmcnatovvfxodiqwzrkwfzabhfkcknncirmjcqudafaqizduwzbtblqzxxwzzsvcvatilvcbpljrwyfbexmvnejtycgjymajunvlgbizcxbgeigcvcprhmuhlejpzyyhvjcwiuqbdagbqbqzfhvgzeyivksbpxmhqvtncynsyzgeknjrrhgcfnhihumgxbzrefzgbvaxvxhedzvdzebmxdzgzifyfyyfcluccaxzmbylktrprawebqgmukxgtlouwcruomaogosltkvevyolusgitgqyqcbryhxwtonkyehpctiqwvdatpfzljwwtlnxrbqdssalqnhefzaoebzmrbardwbmsfoxcsgnajyruawypwqtqxwfrhqwsusyrckghuqjciofzfcfsddrvnkhjhmmtsqpiimkobwlhdmsinglfwuutcepcoianuudwrdeikmukrdajzsymarepqbvuqcjegwyharjqphmnibwzucoxsezkvgownrcgjsmttquiahqvywdftsmpvyofbwntkgkfplxnetgmdfawjkpaigitkfveurgwzjsgwuynilnmbmdzawsrbtetpmtipqpalvatzhaihvrjvmseyuvpowzvnsdekkgbdcngnjykryoiqyeecbooghnridvykantprptapkidkpgdqvoafthbupeglxlumyyxwykgvbjcamwqwbkjluqynygybwztbqraafrarrpfodreeeykixkgrolgqjdcqc";
    //string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    //string str = "nnpxouomcofdjuujloanjimymadkuepightrfodmauhrsy";
    //string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //string str = "abcd";
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //string str = "nnpxouomcofdjuujloanjimymadkuepightrfodmauhrsy";
    //string str = "polxtvqlurgobbzbjcjsupskvzmtuveuavrzcxaifmdwqjbuejdasuxcvsupqnucorfawncjqkbakilhiekavhmsjbtlsfydijafxhgrgbsswtnvdquwokcliaxevairergwdtndsibiulqiutkcwsqpzuyypnhiowgvkkdbpkoyvgwyuqcokjnxluamwnuhqjtaossezwxvkpdkqcleqjkelcludtbigxkueupnxjncrbgvdrsdpppqqcopnwadqsxkvlkghfmtvdeygpyxamvxhmmaunxskgnenobvnzizbxwrjeedisrgzykoaidiffzqzsmirxkvfwmtifywamcpxziyjohcudzelgbmdgiaqwnzdbkwbhdioiokaivzlzscshrvbmggdztjuimribrgmdlcctvldbcxwpqnqbkzrcayqdqraobqcgoxxocclasphcjcydpkgkqhrmmxtklpxfxnrgnzczjxanaltnjhwfatgryqhcllemgqcchiagizpdgiqioqyhrpattutmuotrcwtxvdqzzsomofizebbqrgwruydyawsssjkakjpjlzmfhmjetymftxrhilpcgfqyoohyydnodfortlkeoncmfkdraiqydxcodyapjaxumjwczwmthrcecfgsswwtnyqurvggamjbsjdzmcuyefwnsrnhhpusfdsxbsrsrywbccullupdbovnmzluqsfdhqbef";
    //string str = "abcdab";
    //string str = "djpqwlrroqeuwwqgxnvdftzgsgnmpnhnhezixyhlydjjekpeczwtguowubfjsyohxaihmbjzfchmbnppouguvklmiaqkgomqzvvfubklwexbnzbdkvtxjnpzmfdgomvvsekluemjqaatkbhklusgxbezjghoddwcmirwrnnsgzjzwrnfyqgjylzgwhwipinohhzkywikevsqurnirnmmkgwpgvdswttwpingslbzxzsodqvlluqetfzfzbdhilaugrxewhomtwzjyldxzwtxmufbcrxtqfpcqscbbstplqczhumhedcmmgfkhdyetexcyrlvdrkgxzsncrpoomtqwnwozbteedjozikggwkbexbibruqdpekpjpzzymxpvtsderhjwxvyfahximykcndxskcjwewnfcbvymijwkrisjtzyiegysxpyfdrblxjquytzgvajmdvylemhqcctivjzmkdojbpvucgswycfnjkyoqvzlufphsrvhcbkxamqmaoveycykirpboguhrimemgkkbdmkyvalkpmktlkhwtaafuphdksucgianjkyztzyrndfjhkemdlgnmbucmqqyvjmzqlmgerhvzdtbjsagisjsqnrzqlmimtxumlngktcptgpcevpybghuycisxbemgpwptokdqvzp";
    uint64_t t1 = GetNowUsecs();
    string longeststr = s.longestDupSubstring(str);
    uint64_t t2 = GetNowUsecs();
    cout << "Spend time: " << (t2 - t1)  << "=>" << s.proc_time << endl;
    cout << longeststr << endl;

    cout << "===== Bi ======" << endl;
    t1 = GetNowUsecs();
    string longeststr_bi = s_bi.longestDupSubstring(str);
    t2 = GetNowUsecs();
    cout << "Spend time: " << (t2 - t1) << endl;
    cout << longeststr_bi << endl;
    cout << "Equal? " << (longeststr == longeststr_bi) << endl;


    for(auto iter =  s.pow_cache.begin(); iter != s.pow_cache.end(); ++iter)
    {
        //cout << iter->first.first << "^" << iter->first.second << " = " << iter->second.first << ", " << iter->second.second << endl;
    }
    return 0;
}
