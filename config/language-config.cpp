#include <config/language-config.h>

#include <fstream>

config::LanguageConfig::LanguageConfig(std::string model_language) {
    model_language_ = model_language;
    hid_to_ascii_ = SetHidToAscii();
    special_chars_ascii_ = {};
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

const std::string& config::LanguageConfig::GetModelLanguage() const {
    return model_language_;
}

bool config::LanguageConfig::SetModelLanguage(std::string model_language) {
    model_language_ = model_language;
    const std::optional<std::vector<std::string>>& digraphs =
        ReadNgraph("/digraph.txt");
    const std::optional<std::vector<std::string>>& trigraphs =
        ReadNgraph("/trigraph.txt");
    const std::optional<std::map<int, std::string>>& special_chars =
        ReadSpecial();
    if (digraphs.has_value() && trigraphs.has_value()) {
        digraph_ = std::move(digraphs.value());
        trigraph_ = std::move(trigraphs.value());
        if (special_chars.has_value()) {
            special_chars_ascii_ = std::move(special_chars.value());
        }
        return true;
    } else {
        return false;
    }
}

std::map<int, std::string> config::LanguageConfig::SetHidToAscii() {
    // Use hard-coded hid to ascii map
    // Based on: https://aeb.win.tue.nl/linux/kbd/scancodes-10.html#scancodesets
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

std::vector<std::string> config::LanguageConfig::SetDigraph() {
    std::vector<std::string> digraph = {};

    // If no language was selected, use hard-coded digraphs
    if (model_language_ == "en") {
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

    // If no language was selected, use hard-coded trigraphs
    if (model_language_ == "en") {
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

std::optional<std::vector<std::string>> config::LanguageConfig::ReadNgraph(
    std::string ngraph_path) {
    std::ifstream file("languages/" + model_language_ + ngraph_path);

    if (file.is_open()) {
        std::vector<std::string> trigraphs;

        std::string line;
        while (getline(file, line)) {
            trigraphs.push_back(line);
        }
        file.close();
        return trigraphs;
    } else {
        return std::nullopt;
    }
}
std::optional<std::map<int, std::string>>
config::LanguageConfig::ReadSpecial() {
    std::ifstream file("languages/" + model_language_ + "/special.txt");

    if (file.is_open()) {
        std::map<int, std::string> special_chars_ascii;

        int key;
        std::string value;

        while (file >> key >> value) {
            special_chars_ascii[key] = value;
        }
        file.close();
        return special_chars_ascii;
    } else {
        return std::nullopt;
    }
}