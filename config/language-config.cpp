#include <config/language-config.h>

config::LanguageConfig::LanguageConfig(std::string model_language) {
    model_language_ = model_language;
    hid_to_ascii_ = SetHidToAscii();
    special_chars_ascii_ = SetSpecialCharsAscii();
    digraph_ = SetDigraph();
    trigraph_ = SetTrigraph();
    modifier_keys_ascii_ = SetModifierKeys();
}

const std::map<int, std::string>& config::LanguageConfig::GetHidToAscii()
    const {
    return hid_to_ascii_;
}

const std::map<int, std::string>& config::LanguageConfig::GetSpecialCharsAscii()
    const {
    return special_chars_ascii_;
}

const std::map<int, std::string>& config::LanguageConfig::GetModifierKeys()
    const {
    return modifier_keys_ascii_;
}

const std::vector<std::string>& config::LanguageConfig::GetDigraph() const {
    return digraph_;
}

const std::vector<std::string>& config::LanguageConfig::GetTrigraph() const {
    return trigraph_;
}

std::map<int, std::string> config::LanguageConfig::SetHidToAscii() {
    std::map<int, std::string> hid_to_ascii = {
        {53, "`"},          {30, "1"},         {31, "2"},
        {32, "3"},          {33, "4"},         {34, "5"},
        {35, "6"},          {36, "7"},         {37, "8"},
        {38, "9"},          {39, "0"},         {45, "-"},
        {46, "="},          {42, "Backspace"}, {43, "Tab"},
        {20, "q"},          {26, "w"},         {8, "e"},
        {21, "r"},          {23, "t"},         {28, "y"},
        {24, "u"},          {12, "i"},         {18, "o"},
        {19, "p"},          {47, "["},         {48, "]"},
        {49, "\\"},         {57, "CapsLock"},  {4, "a"},
        {22, "s"},          {7, "d"},          {9, "f"},
        {10, "g"},          {11, "h"},         {13, "j"},
        {14, "k"},          {15, "l"},         {51, ";"},
        {52, "'"},          {40, "Enter"},     {225, "LShift"},
        {29, "z"},          {27, "x"},         {6, "c"},
        {25, "v"},          {5, "b"},          {17, "n"},
        {16, "m"},          {54, ","},         {55, "."},
        {56, "/"},          {229, "RShift"},   {224, "LCtrl"},
        {226, "LAlt"},      {44, "Space"},     {230, "RAlt"},
        {228, "RCtrl"},     {73, "Insert"},    {76, "Delete"},
        {74, "Home"},       {77, "End"},       {75, "PgUp"},
        {78, "PgDn"},       {80, "Left"},      {82, "Up"},
        {81, "Down"},       {79, "Right"},     {83, "NumLock"},
        {41, "Esc"},        {58, "F1"},        {59, "F2"},
        {60, "F3"},         {61, "F4"},        {62, "F5"},
        {63, "F6"},         {64, "F7"},        {65, "F8"},
        {66, "F9"},         {67, "F10"},       {68, "F11"},
        {69, "F12"},        {70, "PrtScr"},    {71, "ScrollLock"},
        {72, "Pause"},      {227, "LWin"},     {231, "Rwin"},
        {229, "RShift"},    {224, "LCtrl"},    {226, "LAlt"},
        {230, "RAlt"},      {228, "RCtrl"},    {73, "Insert"},
        {76, "Delete"},     {74, "Home"},      {77, "End"},
        {75, "PgUp"},       {78, "PgDn"},      {80, "Left"},
        {82, "Up"},         {81, "Down"},      {79, "Right"},
        {83, "NumLock"},    {41, "Esc"},       {58, "F1"},
        {59, "F2"},         {60, "F3"},        {61, "F4"},
        {62, "F5"},         {63, "F6"},        {64, "F7"},
        {65, "F8"},         {66, "F9"},        {67, "F10"},
        {68, "F11"},        {69, "F12"},       {70, "PrtScr"},
        {71, "ScrollLock"}, {72, "Pause"},     {227, "LWin"},
        {231, "Rwin"},      {57, "CapsLock"},  {42, "Backspace"},
        {43, "Tab"},        {40, "Enter"},     {225, "LShift"},
        {1033, "Fn"},       {101, "Menu"}};

    return hid_to_ascii;
}

std::map<int, std::string> config::LanguageConfig::SetModifierKeys() {
    std::map<int, std::string> modifier_keys_ascii = {
        {229, "RShift"},
        {230, "RAlt"},
        {225, "LShift"},
    };

    return modifier_keys_ascii;
}

std::map<int, std::string> config::LanguageConfig::SetSpecialCharsAscii() {
    std::map<int, std::string> special_ascii = {};
    if (model_language_ == "PL") {
        special_ascii = {{8, "ę"},  {4, "ą"},  {22, "ś"}, {15, "ł"}, {29, "ż"},
                         {27, "ź"}, {18, "ó"}, {6, "ć"},  {17, "ń"}};
    }
    return special_ascii;
}

std::vector<std::string> config::LanguageConfig::SetDigraph() {
    std::vector<std::string> digraph = {};
    if (model_language_ == "PL") {
        digraph = {
            "ni", "ie", "ow", "an", "wa", "za", "po", "ał", "ch", "ia", "ko",
            "rz", "mi", "ro", "cz", "ci", "wy", "li", "em", "wi", "by", "sz",
            "na", "ym", "ze", "ac", "ka", "er", "ar", "sk", "ra", "pr", "am",
            "od", "ła", "on", "al", "zy", "ne", "en", "st", "om", "ąc", "uj",
            "to", "ki", "ny", "ją", "no", "aj", "my", "ej", "ta", "yc", "io",
            "go", "ep", "or", "at", "tr", "la", "eg", "as", "es", "oz", "yś",
            "do", "ty", "ob", "os", "pi", "ły", "cy", "lo", "mu", "ło", "zo",
            "yw", "ce", "le", "ad", "ma", "ek", "dz", "ic", "in", "ab", "śc",
            "we", "pa", "ry", "el", "ol", "ew", "ec", "op", "aw", "te", "re",
            "mo", "ku", "ot", "kr", "bi", "et", "ak", "zi", "zn", "ap", "ez",
            "ed", "ga", "oc", "śm", "ok", "ru", "us", "ur", "ys", "is", "je",
            "ik", "si", "łb", "ił", "wo", "so", "ię", "og", "yk", "yb", "tu",
            "ws", "eo", "oś", "ca", "da", "gr", "de", "iz", "ną", "nt", "iu",
            "sp", "ba", "ja", "łe", "ów", "il", "ań", "sa", "zc", "ib", "br",
            "zk", "dr", "zu", "ha", "im", "yn", "uc", "rs", "me", "yt", "bo",
            "lu", "zm", "iw", "eb", "że", "yp", "it", "nk", "ul", "pe", "ag",
            "iś", "ln", "sy", "jc", "fi", "up", "jm", "kl", "ńs", "co", "ut",
            "uk", "eś", "eż", "rn", "rk", "dy", "yj", "ho", "ęc", "ck", "pl",
            "ią", "łu", "yz", "tk", "gi", "dn", "ud", "aś", "yl", "su", "az",
            "bu", "ył", "wn", "wu", "be", "um", "yż", "ża", "se", "cj", "pu",
            "ks", "tw", "eu", "zw", "zą", "ką", "jo", "fo", "yd", "nd", "ij",
            "tn", "rc", "jn", "du", "rt", "ęt", "un", "js", "zd", "ub", "wc",
            "aż", "ró", "wą", "ży", "gn", "eń", "nu", "sc", "pł", "yg", "ri",
            "fa", "bl", "zg", "oż", "cą", "kt", "oł", "dw", "sł", "oo", "uw",
            "nę", "wk", "rd", "ea", "gl", "af", "dk", "zę", "oj", "zb", "kn",
            "kł", "of", "eł", "id", "rm", "py", "zp", "ds", "śl", "ef", "ół",
            "dp", "śn", "ng", "nc", "zt", "gł", "yr", "rę", "ns", "ęd", "jż",
            "di", "dł", "ać", "ir", "dl", "rw", "kw", "gu", "pó", "he", "ję",
            "hi", "zr", "żo", "sm", "au", "ge", "mp", "ig", "nn", "zl", "fe",
            "rą", "zł", "łk", "ps", "ug", "uz", "św", "lk", "rg", "fr", "ip",
            "ls", "żn", "hu", "ńc", "rb", "hr", "ąd", "ęł", "zs", "yf", "kę",
            "dc", "ęk", "oi", "ęb", "dm", "pt", "bn", "mn", "pn", "bs", "cu",
            "ei", "hn", "dż", "tł", "kó", "wr", "tę", "lc", "hl", "ść", "uł",
            "mb", "ęg", "bł", "hy", "fl", "ti", "fu", "uż", "tą", "tl", "lą",
            "ou", "ór", "lt", "sn", "ęż", "wę", "wł", "rp", "pc", "dg", "ąt",
            "ai", "mr", "zj", "uś", "wp", "ee", "kc", "dź", "pę", "ąg", "iń",
            "ęp", "łą", "tó", "jk", "wz", "lę", "źn", "eh", "db", "sf", "łó",
            "óż", "ęs", "oń", "ll", "hł", "ju", "ke", "ąs", "rl", "ął", "ąb",
            "bk", "hw", "gw", "ao", "ua", "łę", "łt", "oa", "ój", "dt", "oh",
            "mó", "żu", "ąk", "ms", "uf", "rf", "if", "ęl", "yń", "wl", "ąż",
            "żd", "wt", "ió", "dd", "bc", "ąz", "gó", "łc", "lm", "śr", "tc",
            "są", "wd", "óc", "ah", "jd", "żk", "lg", "mk", "nf", "nó", "sj",
            "sr", "ct", "uo", "rż", "łz", "pk", "yo", "wó", "eź", "mł", "żó",
            "mę", "źw", "ht", "cc", "iż", "łn", "żą", "zż", "oe", "ód", "ss",
            "sl", "ić", "jt", "ft", "wm", "gm", "bw", "łg", "sw", "bm", "hm",
            "lw", "lb", "zó", "ji", "mą", "nw", "ld", "rł", "zh", "có", "ii",
            "gę", "łs", "ćw", "dę", "bd", "bt", "dą", "ml", "śp", "ęć", "ńk",
            "cn", "ęz", "só", "ae", "łd", "aa", "nz", "zz", "ąp", "ób", "eć",
            "aź", "dj", "rr", "bó", "cę", "wg", "wś", "ól", "yh", "tt", "bz",
            "źc", "dó", "ue", "ló", "jr", "bę", "źd", "yć", "dś", "ós", "gz",
            "tm", "lż", "łp", "ui", "mc", "ts", "ęś", "dh", "źm", "oź", "uź",
            "ww", "gd", "sę", "mf", "hc", "zś", "df", "lf", "źl", "ćm", "łw",
            "nż", "mm", "żl", "ye", "sh", "ćk", "uń", "lp", "jp", "jl", "bą",
            "ót", "bj", "pp", "cm", "żc", "żł", "żm", "km", "łm", "ya", "jz",
            "cr", "hó", "żę", "cl", "gą", "ąć", "żs", "ćc", "bb", "kp", "śk",
            "yi", "hę", "óź", "ók", "ąw", "yu", "oć", "mg", "uh", "bg", "óz",
            "iź", "śt", "sb", "uu", "nh", "ff", "źb", "wb", "kk", "th", "wż",
            "bż", "nb", "md", "cw", "fy", "pą", "pm", "ćp", "lś", "źg", "yź",
            "łż", "jó", "jw", "ih", "źż", "źr", "bś", "ńm", "jb", "ęź", "jg",
            "ay", "jś", "żi", "fn", "ąś", "fk", "tp", "łr", "żw", "żb", "gh",
            "jf", "zf", "rć", "tb", "rś", "mż", "tf", "ćż", "łź", "uć", "gg",
            "żż", "ph", "rź", "rń", "hs", "ey", "nl", "pż", "żg", "lz", "ńb",
            "wj", "gb", "mt", "fc", "łł", "cł", "łl", "nr", "ńż", "fs", "rh",
            "tg", "gs", "fó", "kh", "hą", "ly", "gy", "sg", "ky", "mś", "bh",
            "lh", "łf", "mw", "żr", "jł", "łś", "śż", "oy", "sd", "kf", "nm",
            "bź", "gt", "nj", "tz", "ex", "cp", "bf", "pd", "łi", "np", "iv",
            "kd", "zć", "óć", "łć", "ńt", "kb", "lń", "jj", "hb", "ćs", "td",
            "óg", "pg", "dć", "eó", "pf", "fm", "cb", "gc", "hp", "kś", "hd",
            "xa", "jh", "gp", "xo", "łj", "mh", "gk", "żp", "pś", "ox", "fą",
            "mz", "fb", "łh", "gż", "ix", "ńd", "tj", "cs", "pj", "fę", "hh",
            "źi", "fg", "ćf", "łń", "ęw", "rj", "pć", "ax", "eą", "ćd", "ąź",
            "źć", "wh", "lr", "gj", "lj", "ux", "xi", "źń", "xy", "cg", "eę",
            "va", "xe", "xó", "ćt", "hj", "lź", "vo", "hć", "óś", "ću", "źk",
            "bp", "źa", "yó", "će", "śb", "źp", "kż", "xu", "hk", "vu", "fw",
            "hz", "śa", "sż", "uy", "jń", "kj", "śi", "ća", "ćn", "vi", "ęr",
            "cd", "śń", "żń", "mj", "ve", "óp", "nł", "pb", "hś", "fż", "vy",
            "wf", "kg", "fh", "hg", "vó", "hż", "pw", "mć", "źs", "ąf", "jć",
            "av", "yy", "tż", "fp", "ov", "ćl", "gf", "śu", "śj", "ćb", "uó",
            "żj", "jź", "fd", "bć", "uą", "uę", "śs", "żt", "nć", "ńć", "oą",
            "oę", "źo", "yą", "yę", "vą", "vę", "ói", "jy", "ńa", "oó", "iy",
            "ęn", "óm", "źą", "źe", "źę", "ńo", "aó", "xą", "xę", "ąj", "ąn",
            "gś", "iq", "qu", "mń", "ćś", "śś", "nś", "gź", "ńą", "ńe", "ńę",
            "ńi", "wć", "pń"};
    } else if (model_language_ == "EN") {
        digraph = {
            "er", "in", "ti", "on", "es", "te", "at", "al", "an", "re", "en",
            "is", "ic", "ri", "ra", "le", "st", "li", "ne", "ar", "ro", "ed",
            "ng", "nt", "or", "un", "la", "it", "co", "ca", "ni", "de", "io",
            "to", "ta", "ss", "se", "ia", "no", "tr", "ly", "us", "ch", "ma",
            "el", "ou", "di", "lo", "me", "he", "ll", "na", "ol", "et", "mi",
            "si", "ac", "ve", "pe", "om", "ph", "as", "th", "il", "os", "nd",
            "ea", "ce", "op", "ho", "pr", "hi", "ns", "id", "ur", "ul", "ha",
            "nc", "ie", "ab", "ec", "ot", "em", "po", "pa", "mo", "bl", "ge",
            "rs", "ci", "am", "sh", "oc", "og", "ap", "su", "ct", "pi", "ad",
            "sc", "ut", "sa", "bi", "be", "so", "um", "ba", "da", "ep", "sp",
            "ag", "gi", "rt", "iz", "iv", "im", "cr", "do", "hy", "ke", "cu",
            "od", "ga", "ry", "oo", "ty", "pl", "ee", "tu", "ir", "sm", "gr",
            "ig", "ip", "fi", "bo", "mp", "vi", "lu", "rm", "ai", "ck", "ov",
            "ze", "if", "ae", "br", "ru", "tt", "oi", "qu", "rr", "rc", "ts",
            "rd", "gl", "fo", "eo", "au", "ub", "ex", "fe", "cl", "up", "dr",
            "va", "wa", "go", "ob", "ib", "bu", "pt", "uc", "ki", "eu", "ow",
            "ei", "mb", "rn", "eg", "ui", "ua", "fl", "hr", "mu", "nn", "fu",
            "ps", "yl", "gu", "pu", "ef", "sl", "yp", "oa", "ud", "ys", "wi",
            "pp", "fa", "cy", "lt", "rp", "av", "we", "tl", "ue", "du", "mm",
            "nf", "ev", "nu", "rg", "wo", "rb", "ff", "ak", "eb", "dl", "sy",
            "ls", "gh", "oe", "fr", "rl", "my", "hu", "gn", "ds", "ik", "ay",
            "sn", "vo", "np", "ht", "za", "ym", "cc", "ew", "ug", "ka", "yn",
            "ld", "zi", "yc", "iu", "nk", "yt", "af", "of", "xi", "gg", "ya",
            "nr", "rh", "gy", "yr", "ox", "aw", "rk", "ms", "zo", "nv", "sk",
            "dd", "nl", "py", "hl", "ok", "dy", "tc", "ks", "ny", "ey", "rv",
            "bb", "ye", "yo", "gs", "nm", "bs", "rf", "yd", "az", "ju", "eh",
            "wh", "lp", "ah", "yi", "dn", "nb", "sw", "nh", "lm", "ja", "lc",
            "ax", "ft", "kl", "xt", "tw", "xe", "lv", "ln", "oy", "je", "xa",
            "uo", "ko", "cs", "dg", "jo", "oh", "sq", "mn", "hn", "xp", "uf",
            "wn", "lf", "fy", "nw", "eq", "yg", "hm", "rw", "lk", "tm", "lg",
            "gm", "hs", "kn", "ix", "oz", "xo", "xy", "tf", "lb", "wr", "ws",
            "tn", "ek", "ky", "dm", "wl", "xc", "by", "ii", "zz", "pn", "tb",
            "uk", "nz", "nj", "iq", "dw", "bt", "nq", "sf", "ku", "sb", "dh",
            "yb", "kh", "vu", "bd", "uv", "ez", "zy", "ih", "ji", "hw", "ux",
            "ej", "tp", "kr", "bc", "ao", "ml", "dv", "db", "df", "aq", "tz",
            "oq", "aj", "fs", "yw", "hb", "lw", "kw", "dj", "xu", "sr", "uz",
            "tg", "sg", "zl", "lh", "hf", "kt", "kb", "bj", "sd", "aa", "wd",
            "wb", "km", "bm", "mf", "cn", "yf", "pm", "yz", "yu", "gt", "gw",
            "yh", "bp", "pb", "dc", "yx", "gb", "td", "kf", "xh", "bh", "pw",
            "lr", "dp", "rj", "hp", "wk", "cq", "pf", "bn", "wt", "wy", "oj",
            "uy", "iw", "rq", "dt", "wm", "bf", "pc", "bv", "kp", "hd", "wf",
            "vy", "kk", "ij", "zu", "sv", "gd", "mr", "gf", "rz", "hc", "hh",
            "wu", "nx", "vr", "uh", "wp", "mt", "mc", "xs", "pd", "mw", "md",
            "iy", "bg", "yk", "ww", "tv", "mh", "uj", "mv", "bw", "hg", "pg",
            "wc", "sj", "pk", "uu", "gp", "tk", "tj", "hk", "kd", "xl", "kc",
            "cd", "cm", "lz", "wg", "fb", "dk", "fm", "cz", "fn", "vv", "cp",
            "fw", "fh", "uq", "xb", "xf", "dz", "fd", "fc", "yv", "mg", "xw",
            "bk", "mk", "kg", "gk", "gc", "xm", "hv", "uw", "kv", "fp", "vs",
            "kj", "fg", "cb", "zb", "zd", "qa", "lj", "pj", "cw", "wz", "sz",
            "tq", "lq", "cf", "vl", "mj", "hz", "xd", "zw", "qi", "zp", "zc",
            "jn", "zh", "mz", "hj", "zs", "zm", "zt", "zk", "cg", "vn", "xr",
            "xn", "xg", "xq", "rx", "fk", "zn", "dq", "hq", "gj", "gz", "zr",
            "jr", "bz", "lx", "xx", "yj", "bq", "yy", "zg", "vd", "jd", "zv",
            "vt", "jh", "vg", "pv", "fj", "xv", "qt", "jy", "vc", "tx", "fz",
            "jj", "mq", "vk", "qr", "qe", "wj", "qs", "gv", "yq", "jc", "bx",
            "vz", "qo", "jm", "zq", "pq", "jk", "qq", "kz", "jt", "jp", "jl",
            "js", "fx", "vp", "zf", "vm", "fv", "qw", "jw", "xk", "wq", "vw",
            "cv", "wv", "dx", "qp", "qh", "qn", "jb", "jg", "zj", "ql", "qv",
            "qd", "cx", "px", "jv", "kq", "xz", "vh", "kx", "pz", "mx", "gq",
            "qg", "qy", "qm", "qf", "vb"};
    }
    return digraph;
}

std::vector<std::string> config::LanguageConfig::SetTrigraph() {
    std::vector<std::string> trigraph = {};
    if (model_language_ == "PL") {
        trigraph = {
            "nie", "owa", "ani", "wan", "cie", "nia", "wał", "jąc", "prz",
            "rze", "kow", "owy", "ach", "ami", "ści", "eni", "ała", "ali",
            "ego", "rzy", "iep", "ych", "ane", "emu", "owi", "ywa", "any",
            "ują", "byś", "roz", "ymi", "tow", "iem", "row", "ier", "owe",
            "nym", "ski", "ały", "ają", "iew", "ien", "łby", "śmy", "kie",
            "cza", "now", "łab", "ące", "ący", "aby", "pod", "ies", "nio",
            "ian", "dzi", "zan", "wie", "zow", "czn", "iez", "sko", "wym",
            "cze", "epo", "ieo", "pow", "wal", "czy", "iom", "ałb", "yśm",
            "lib", "low", "wia", "ero", "iby", "iał", "icz", "yby", "iac",
            "łyb", "iej", "iek", "nej", "iel", "ało", "str", "bym", "zcz",
            "sza", "esz", "niu", "nem", "iam", "szc", "ied", "dow", "acz",
            "sow", "awi", "nic", "liś", "iec", "yśc", "szy", "ałe", "jmy",
            "neg", "asz", "ana", "łyś", "ano", "sta", "ośc", "jci", "nyc",
            "pie", "ska", "ńsk", "one", "ycz", "trz", "mie", "uje", "wyw",
            "ono", "zen", "kom", "zał", "ion", "nię", "zon", "wyc", "ony",
            "ież", "oni", "cym", "ato", "usz", "wat", "cha", "rza", "łam",
            "era", "ist", "wsk", "ter", "ewy", "lan", "oro", "cia", "eza",
            "ows", "ieg", "zac", "olo", "arz", "ran", "ost", "ecz", "poz",
            "aty", "aln", "kan", "tro", "tra", "cho", "kim", "rsk", "kar",
            "ast", "iet", "nik", "tyc", "epr", "sze", "ona", "osz", "kuj",
            "iow", "łem", "łow", "mow", "oli", "pos", "ocz", "zaj", "eci",
            "aną", "zni", "oby", "ili", "zes", "kam", "sto", "zie", "kac",
            "czk", "myż", "tor", "tan", "łob", "ena", "aci", "czo", "pro",
            "gra", "cow", "iwa", "dza", "łaś", "eli", "koś", "gow", "adz",
            "rac", "łeś", "zas", "rni", "ieb", "ową", "kon", "ant", "aro",
            "wys", "nad", "liz", "ata", "wyp", "est", "ieu", "bie", "iko",
            "cio", "sty", "wej", "zuj", "tuj", "ęci", "zar", "ewa", "wuj",
            "pop", "por", "odz", "zak", "ąca", "zap", "ala", "eka", "dni",
            "ank", "uch", "yjn", "cki", "zył", "iaj", "wem", "iśm", "ięc",
            "ars", "erz", "iśc", "mar", "iła", "ini", "izo", "epi", "ięt",
            "ada", "ent", "ich", "opi", "zko", "ako", "eko", "pra", "szo",
            "oto", "sie", "ącą", "yst", "zep", "jże", "owu", "weg", "etr",
            "omi", "wni", "oza", "ino", "iar", "ina", "par", "ara", "ech",
            "zam", "amo", "tar", "tni", "ate", "pia", "cyj", "yka", "śni",
            "wań", "nac", "acj", "odo", "odp", "lin", "ods", "ujm", "wsz",
            "arn", "zer", "ste", "bia", "log", "nko", "ele", "zyk", "iły",
            "len", "ruj", "cem", "elo", "och", "cej", "opo", "ela", "oko",
            "wyk", "kra", "per", "ańs", "ujc", "kro", "rko", "imi", "sku",
            "ark", "raw", "naw", "war", "lni", "mia", "ika", "gan", "rom",
            "lic", "zys", "edo", "owo", "emi", "ole", "ota", "zyw", "eod",
            "lon", "pok", "krz", "ryz", "tac", "tko", "ajm", "zal", "owc",
            "nas", "man", "ajc", "oma", "rad", "nto", "alo", "min", "obr",
            "ewi", "eto", "pół", "api", "tyw", "ers", "ask", "kal", "zna",
            "odk", "uro", "pol", "opr", "zyc", "awa", "zek", "pan", "zyn",
            "ejs", "cią", "pom", "naj", "uwa", "cyc", "art", "tal", "emy",
            "zem", "yko", "ogr", "dro", "try", "świ", "ceg", "wic", "ras",
            "acy", "abi", "ado", "kic", "poo", "ros", "zaw", "nam", "opa",
            "zne", "ysz", "cen", "ład", "ron", "arc", "ale", "zew", "aka",
            "zny", "ram", "obi", "skr", "niz", "pon", "orz", "tym", "waj",
            "iea", "wac", "rzę", "kiw", "szk", "rzą", "liw", "bow", "pla",
            "gni", "ozp", "zec", "aso", "ogi", "okr", "kał", "ory", "kop",
            "odr", "stw", "ora", "tyk", "zym", "jsk", "apa", "tur", "yli",
            "ito", "epa", "chr", "mat", "osk", "uto", "ery", "kol", "lis",
            "rod", "noś", "spo", "tom", "ema", "tał", "nap", "kni", "osi",
            "ząc", "esk", "pot", "ucz", "poc", "kor", "bra", "tru", "mac",
            "zel", "scy", "own", "wyt", "omo", "met", "ety", "kle", "eks",
            "eta", "atr", "raj", "brz", "nty", "zia", "ust", "yła", "ryw",
            "tem", "zat", "chn", "lał", "rat", "dos", "szt", "ial", "nęł",
            "oci", "oka", "ską", "ama", "eob", "pas", "lat", "rop", "las",
            "eno", "ere", "pal", "and", "ick", "nom", "mon", "urz", "nił",
            "rzo", "nis", "ary", "jem", "isz", "zka", "aja", "rcz", "ówk",
            "odn", "ern", "edz", "udz", "lep", "emo", "zab", "rob", "isk",
            "raf", "yci", "how", "ing", "lek", "pła", "gar", "ysk", "apo",
            "jec", "kła", "sam", "ega", "cjo", "rys", "ula", "zma", "izm",
            "chl", "aws", "zyt", "laj", "kaj", "dra", "izu", "jes", "lam",
            "jan", "wyd", "zad", "kli", "lar", "yna", "luj", "odw", "ryc",
            "apr", "tyz", "spa", "yno", "zag", "ral", "nan", "lit", "zmi",
            "amy", "yni", "zed", "dze", "grz", "cja", "dan", "ził", "tam",
            "ędz", "nij", "kur", "wio", "nar", "lił", "nal", "czu", "stk",
            "sia", "bez", "iłb", "rot", "ywi", "ton", "ban", "ość", "men",
            "can", "erk", "wyr", "ome", "lik", "yto", "wać", "rab", "han",
            "iło", "yzo", "iad", "bio", "kre", "win", "edn", "ęcz", "zwi",
            "rto", "nin", "ont", "res", "oty", "odc", "jon", "nuj", "jsz",
            "bro", "pyw", "rka", "uję", "otr", "nka", "ień", "ogo", "bar",
            "dop", "kla", "chi", "łac", "lej", "rów", "spr", "for", "ekt",
            "upi", "lac", "spi", "awo", "nat", "uka", "ija", "aża", "ków",
            "kto", "rus", "pat", "mal", "anc", "tka", "yta", "stu", "ote",
            "wyb", "rap", "ujż", "taw", "aga", "ekr", "mor", "asi", "lne",
            "wko", "ura", "łko", "taj", "eru", "kos", "umi", "kas", "dom",
            "ief", "lec", "der", "cił", "roc", "fil", "suj", "czą", "pog",
            "kat", "oną", "żni", "pis", "ita", "pob", "mio", "esp", "żow",
            "oga", "zyp", "gro", "ypi", "lny", "gry", "pre", "kul", "iat",
            "san", "esi", "rwi", "ola", "twi", "obs", "kap", "ors", "zeg",
            "eck", "śmi", "akt", "obo", "jow", "jed", "oso", "mię", "cko",
            "akr", "żan", "dwu", "nte", "zeb", "wyg", "atu", "wod", "zwa",
            "rem", "ypa", "dzo", "ozs", "iza", "aki", "lew", "kwi", "aca",
            "ozk", "nos", "gen", "nak", "ącz", "tyn", "tel", "wow", "ryt",
            "afi", "śli", "har", "ico", "eńs", "kry", "oba", "odm", "rak",
            "raż", "uko", "ozw", "szu", "ard", "lsk", "ebr", "ofi", "nta",
            "tol", "sma", "twa", "ław", "dok", "zmy", "zyd", "pni", "wer",
            "puj", "zyl", "ici", "dko", "yma", "ode", "jne", "aku", "duj",
            "ieł", "aba", "mer", "dno", "kot", "ebi", "eso", "zej", "ręc",
            "odg", "jny", "eba", "żen", "ciu", "eje", "ngo", "rek", "gło",
            "zio", "rał", "enn", "erd", "ene", "gał", "agr", "wis", "zki",
            "mas", "żon", "uni", "bur", "krę", "cał", "ńcz", "ans", "mni",
            "fik", "ren", "ulo", "top", "eku", "ner", "egr", "ore", "kwa",
            "oku", "leg", "ajż", "łos", "rol", "erm", "ozm", "pio", "ndo",
            "int", "ort", "wił", "sło", "dol", "chł", "bni", "ubi", "sła",
            "jni", "ria", "ywn", "nit", "zło", "dob", "łod", "ińs", "upo",
            "iki", "asa", "tów", "mot", "ilo", "iłe", "łas", "wil", "ple",
            "zyg", "źni", "yły", "dal", "udo", "ieś", "rzu", "ack", "yku",
            "iku", "dys", "lko", "rst", "zmo", "con", "ser", "teg", "obl",
            "erw", "ozo", "rdz", "nag", "yfi", "iąc", "pin", "dor", "byw",
            "hni", "sad", "ntr", "chu", "ańc", "ler", "rec", "ago", "zgr",
            "azo", "bor", "ryn", "koc", "gal", "usk", "usi", "yga", "pac",
            "arb", "chw", "rog", "uci", "tre", "pię", "sch", "dar", "wid",
            "pał", "yla", "two", "ekl", "cis", "guj", "mik", "uli", "oru",
            "oło", "bli", "let", "wit", "pił", "ret", "ink", "are", "glo",
            "drz", "rud", "pou", "bal", "ęty", "opl", "iwi", "rok", "wią",
            "orn", "che", "ębi", "ede", "ylo", "eja", "yzm", "eją", "enc",
            "wor", "tej", "erc", "tat", "łon", "iań", "dli", "ytr", "ood",
            "oży"};
    } else if (model_language_ == "EN") {
        trigraph = {
            "ing", "ati", "ess", "ion", "ter", "nes", "tio", "ate", "ent",
            "ous", "tic", "ica", "ist", "cal", "ers", "ble", "non", "ant",
            "per", "all", "ine", "ver", "eri", "tin", "abl", "ali", "pre",
            "tra", "con", "lin", "ted", "sti", "ive", "nte", "ene", "rat",
            "res", "tri", "ies", "est", "oni", "pro", "nti", "men", "tor",
            "lat", "ite", "ari", "ove", "lit", "lly", "rin", "ste", "iti",
            "ize", "der", "the", "era", "nde", "les", "ran", "int", "ism",
            "ere", "str", "dis", "ast", "gra", "ons", "her", "ili", "ian",
            "ric", "man", "ona", "ato", "mat", "olo", "ect", "oph", "ero",
            "tro", "ina", "tiv", "ity", "log", "und", "ria", "one", "ula",
            "ani", "chi", "pho", "min", "red", "ome", "sta", "ori", "nat",
            "ial", "ell", "ish", "cti", "emi", "lis", "and", "cat", "rop",
            "che", "nis", "nal", "ill", "met", "nce", "ele", "ise", "par",
            "for", "ost", "ide", "mis", "rap", "rac", "rea", "nic", "ris",
            "phi", "tal", "cha", "lar", "ini", "ace", "oma", "sto", "lli",
            "rec", "eli", "gen", "com", "len", "oli", "nta", "aph", "car",
            "mon", "tat", "ten", "tis", "unc", "erm", "lan", "sub", "anc",
            "rou", "cul", "mic", "enc", "ete", "sis", "lic", "ral", "ard",
            "out", "pha", "ros", "nin", "tom", "ont", "eti", "art", "rit",
            "ara", "ida", "end", "ort", "sin", "eni", "ore", "ici", "tes",
            "pla", "lle", "act", "ron", "ngl", "ang", "lla", "tur", "oid",
            "uns", "cho", "led", "rom", "ler", "ssi", "ndi", "ath", "phy",
            "din", "ner", "ure", "ret", "ita", "osi", "ora", "shi", "ogi",
            "etr", "tan", "age", "nit", "hor", "ach", "ses", "tho", "ono",
            "den", "tte", "nco", "dia", "rie", "bil", "hal", "mer", "oto",
            "ens", "ier", "ass", "cro", "ntr", "nia", "unt", "las", "hin",
            "ans", "cor", "sup", "ton", "ven", "rot", "uri", "kin", "har",
            "ale", "ino", "ala", "erc", "ser", "ber", "ogr", "ind", "ins",
            "omi", "cen", "orm", "qui", "idi", "ana", "sco", "liz", "ren",
            "pol", "eno", "ely", "col", "nch", "roc", "gly", "sse", "iat",
            "ose", "pin", "pos", "sem", "eme", "bra", "hea", "iou", "tar",
            "ert", "han", "esi", "des", "ful", "nge", "tab", "arc", "ami",
            "hro", "ack", "por", "ger", "ema", "abi", "ain", "thi", "rti",
            "ond", "inc", "ker", "ole", "upe", "llo", "edi", "onc", "eta",
            "ura", "oun", "ple", "can", "spe", "ear", "fer", "vel", "rep",
            "ifi", "dic", "nth", "ram", "mor", "lia", "she", "tel", "sed",
            "pen", "tre", "pat", "ike", "ane", "oth", "uni", "cer", "eco",
            "hic", "dro", "ary", "ree", "err", "rch", "sio", "ned", "ame",
            "let", "eat", "ata", "hyp", "tie", "ile", "oti", "rid", "mar",
            "are", "ium", "isi", "cra", "ead", "lac", "ade", "adi", "hip",
            "imp", "cto", "omo", "lik", "rio", "tia", "rma", "hol", "sit",
            "oge", "cin", "isc", "ern", "mal", "ith", "ust", "cop", "qua",
            "lec", "ico", "thr", "emo", "wor", "ope", "phe", "nsi", "cou",
            "sne", "oro", "rad", "ola", "ght", "hes", "nar", "ult", "pti",
            "iza", "zin", "ors", "que", "niz", "hem", "sen", "sly", "igh",
            "pan", "unp", "aci", "hil", "oll", "app", "dae", "oly", "ras",
            "ano", "gin", "hon", "rem", "ena", "spi", "ick", "rab", "tit",
            "gic", "una", "alo", "ote", "och", "net", "ela", "dec", "odi",
            "rol", "rel", "our", "ock", "pal", "zed", "pri", "cre", "iss",
            "bar", "opi", "att", "pic", "ong", "omp", "epi", "sal", "mit",
            "ett", "cia", "til", "hen", "asi", "top", "los", "ime", "lor",
            "fic", "eph", "cri", "use", "ded", "lou", "oca", "spo", "opo",
            "rre", "uti", "nto", "eth", "tch", "lea", "ice", "tle", "rog",
            "sha", "ibl", "ery", "nst", "ood", "arr", "roo", "ave", "ode",
            "iso", "amp", "usl", "eal", "bly", "cle", "cke", "riz", "isa",
            "nom", "sca", "scr", "nos", "nne", "rte", "eou", "nse", "mel",
            "ory", "war", "chr", "bro", "his", "cla", "atr", "rmi", "eve",
            "rer", "rai", "tha", "rth", "nci", "ich", "lie", "ept", "erp",
            "erl", "ces", "hed", "ama", "une", "ped", "rdi", "dne", "nou",
            "ake", "rse", "esc", "ase", "sol", "zat", "tru", "son", "tol",
            "nre", "rag", "rri", "aut", "ean", "sur", "med", "ire", "cur",
            "sia", "icu", "cep", "hel", "rus", "loc", "eas", "win", "ann",
            "ngs", "ull", "mas", "nda", "bri", "gat", "ein", "ref", "acc",
            "gis", "ede", "lam", "som", "gal", "dly", "ito", "bal", "erv",
            "unr", "ail", "dra", "mes", "mul", "ien", "izi", "ype", "lum",
            "osp", "odo", "sce", "ima", "cit", "ndo", "ppe", "sat", "ivi",
            "lab", "elo", "omy", "imi", "dit", "dle", "oce", "cel", "tim",
            "usn", "lig", "orn", "hyd", "san", "agi", "tly", "eur", "oss",
            "sor", "hot", "tos", "oco", "uli", "cea", "don", "ord", "pli",
            "aro", "dem", "ogy", "orp", "ila", "ung", "lus", "ese", "sel",
            "ntl", "bac", "ngi", "nsu", "yst", "eci", "ute", "sch", "mpe",
            "uto", "sul", "low", "erg", "opa", "cap", "dio", "erb", "eca",
            "nan", "lot", "aco", "osc", "del", "het", "lon", "nts", "mou",
            "orr", "lio", "rim", "amb", "emp", "pit", "spa", "gon", "oot",
            "gan", "toc", "vin", "tti", "neu", "eed", "itt", "ars", "siv",
            "lop", "mme", "rei", "rif", "ash", "apo", "rig", "icr", "tif",
            "ual", "sts", "ota", "mac", "dom", "obi", "uro", "bel", "thy",
            "reg", "ied", "inf", "nab", "mil", "val", "ril", "ext", "mia",
            "edl", "usi", "ydr", "iol", "nac", "fie", "rip", "ega", "eto",
            "ndr", "fla", "erf", "tac", "pse", "ech", "ban", "ifo", "pec",
            "bla", "gle", "dal", "tem", "ges", "squ", "sci", "onf", "edn",
            "sho", "bli", "ign", "gre", "hou", "pon", "bat", "ily", "arb",
            "vis", "atu", "rev", "omm", "cos", "hom", "bit", "pul", "cid",
            "ilo", "bul", "itu", "lti", "unf", "lne", "nop", "not", "acr",
            "nni", "eud", "ncy", "sma", "mpl", "hoo", "yin", "hyl", "erd",
            "iac", "cas", "cis", "rni", "tai", "sil", "exp", "amm", "nor",
            "mid", "dri", "isp", "ife", "sic", "lim", "bin", "ngu", "duc",
            "fin", "umb", "arm", "cte", "sid", "ict", "rmo", "pte", "coc",
            "lem", "avi", "gar", "amo", "pis", "rod", "glo", "fis", "cli",
            "ssa", "cta", "tiz", "fra", "equ", "gne", "lid", "emb", "iri",
            "clo", "eso", "ape", "ves", "oin", "hos", "pra", "seu", "otr",
            "rna", "pet", "owe", "rme", "mot", "dat", "bre", "mph", "hia",
            "nol", "sph", "aca", "unb", "rge", "udo", "uin", "flo", "dea",
            "leg", "ias", "bor", "rob", "air", "rne", "ctr", "opl", "syn",
            "try", "ago", "rco", "bur", "unm", "rra", "tou", "een", "npr",
            "iva", "mpa", "tas", "nel", "rph", "alt", "arg", "nas", "scu",
            "noc", "uct", "pot", "tid", "ule", "cks", "rde", "bas", "rib",
            "lut", "pod", "row", "aff", "old", "ics", "ked", "ulo", "dan",
            "epr", "ged", "stu", "itr", "lif", "ben", "sec", "rcu", "evi",
            "ott", "ibi", "sar", "vit", "ypo", "pas", "eae", "tog", "rum",
            "reb", "epa", "rli", "cio", "ffe", "pel", "sso", "nif", "esp",
            "ece", "mol", "plo", "hop", "utt", "ysi", "opt", "rsi", "eac",
            "agg", "tea", "bol", "fle", "llu", "die", "abo", "tyl", "als",
            "ced", "ecu", "asc", "ink", "lag", "reo", "roi", "mag", "iga",
            "ork", "olu", "ank", "umi", "vol", "nid", "ume", "ify", "hie",
            "ceo", "oso", "mos", "ush", "pto", "bio", "enn", "api", "onv",
            "mus", "wer", "ipp", "gro", "flu", "nam", "rav", "nca", "cum",
            "nve", "ham", "def", "cus", "ado", "pie", "hag", "ctu", "onp",
            "rro", "ffi", "cie", "udi", "nso", "dep", "aur", "sop", "wee",
            "chl", "ugh", "bed", "mpo", "hys", "tee", "tag", "lep", "ige",
            "woo", "hit", "rta", "gia", "nap", "gas", "uck", "alc", "inn",
            "lip"};
    }
    return trigraph;
}