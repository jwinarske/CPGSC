#include <stdio.h>
#include <sio\siolocal.h>
#include <sio\t4.h>

T4NODE whitetree[], blacktree[], eoltree[];
/*-
ARRAY NAMES:  whitetree, blacktree, eoltree
       TYPE:  Array of T4NODE (typedef)
   FUNCTION:  Each element contains a binary tree node to 
              the T.4 Huffman variable-length.   The eoltree provides
              indefinite looping through zero-fill bits. 
    LIBRARY:  FAX.LIB
*/

T4NODE whitetree[] = {
/* 000 */     {&whitetree[1],   &whitetree[2],   NOTTERMINAL},
/* 001 */     {&whitetree[3],   &whitetree[4],   NOTTERMINAL},
/* 002 */     {&whitetree[5],   &whitetree[6],   NOTTERMINAL},
/* 003 */     {&whitetree[7],   &whitetree[8],   NOTTERMINAL},
/* 004 */     {&whitetree[9],   &whitetree[10],  NOTTERMINAL},
/* 005 */     {&whitetree[11],  &whitetree[12],  NOTTERMINAL},
/* 006 */     {&whitetree[13],  &whitetree[14],  NOTTERMINAL},
/* a */     {&whitetree[15],  &whitetree[16],  NOTTERMINAL},
/* 008 */     {&whitetree[17],  &whitetree[18],  NOTTERMINAL},
/* 009 */     {&whitetree[19],  &whitetree[20],  NOTTERMINAL},
/* 010 */     {&whitetree[21],  &whitetree[22],  NOTTERMINAL},
/* 011 */     {&whitetree[23],  &whitetree[24],  NOTTERMINAL},
/* 012 */     {&whitetree[25],  &whitetree[26],  NOTTERMINAL},
/* 013 */     {&whitetree[27],  &whitetree[28],  NOTTERMINAL},
/* 014 */     {&whitetree[29],  &whitetree[30],  NOTTERMINAL},
/* 015 */     {&whitetree[31],  &whitetree[32],  NOTTERMINAL},
/* 016 */     {&whitetree[33],  &whitetree[34],  NOTTERMINAL},
/* 017 */     {&whitetree[35],  &whitetree[36],  NOTTERMINAL},
/* 018 */     {&whitetree[37],  &whitetree[38],  NOTTERMINAL},
/* 019 */     {&whitetree[39],  &whitetree[40],  NOTTERMINAL},
/* 020 */     {&whitetree[41],  &whitetree[42],  NOTTERMINAL},
/* 021 */     {&whitetree[43],  &whitetree[44],  NOTTERMINAL},
/* 022 */     {&blacktree[1],   &blacktree[2],   2},
/* 023 */     {&blacktree[1],   &blacktree[2],   3},
/* 024 */     {&whitetree[45],  &whitetree[46],  NOTTERMINAL},
/* 025 */     {&whitetree[47],  &whitetree[48],  NOTTERMINAL},
/* 026 */     {&blacktree[1],   &blacktree[2],   4},
/* 027 */     {&blacktree[1],   &blacktree[2],   5},
/* 028 */     {&whitetree[49],  &whitetree[50],  NOTTERMINAL},
/* 029 */     {&blacktree[1],   &blacktree[2],   6},
/* 030 */     {&blacktree[1],   &blacktree[2],   7},
/* 031 */     {&whitetree[51],  &whitetree[52],  NOTTERMINAL},
/* 032 */     {&whitetree[53],  &whitetree[54],  NOTTERMINAL},
/* 033 */     {&whitetree[55],  &whitetree[56],  NOTTERMINAL},
/* 034 */     {&whitetree[57],  &whitetree[58],  NOTTERMINAL},
/* 035 */     {&whitetree[59],  &whitetree[60],  NOTTERMINAL},
/* 036 */     {&whitetree[61],  &whitetree[62],  NOTTERMINAL},
/* 037 */     {&whitetree[63],  &whitetree[64],  NOTTERMINAL},
/* 038 */     {&blacktree[1],   &blacktree[2],   10},
/* 039 */     {&blacktree[1],   &blacktree[2],   11},
/* 040 */     {&whitetree[65],  &whitetree[66],  NOTTERMINAL},
/* 041 */     {&whitetree[67],  &whitetree[68],  NOTTERMINAL},
/* 042 */     {&whitetree[69],  &whitetree[70],  NOTTERMINAL},
/* 043 */     {&whitetree[71],  &whitetree[72],  NOTTERMINAL},
/* 044 */     {&whitetree[73],  &whitetree[74],  NOTTERMINAL},
/* 045 */     {&whitetree[1],   &whitetree[2],   128},
/* 046 */     {&blacktree[1],   &blacktree[2],   8},
/* 047 */     {&blacktree[1],   &blacktree[2],   9},
/* 048 */     {&whitetree[75],  &whitetree[76],  NOTTERMINAL},
/* 049 */     {&whitetree[77],  &whitetree[78],  NOTTERMINAL},
/* 050 */     {&whitetree[1],   &whitetree[2],   64},
/* 051 */     {&whitetree[79],  &whitetree[80],  NOTTERMINAL},
/* 052 */     {&whitetree[81],  &whitetree[82],  NOTTERMINAL},
/* 053 */     {&whitetree[83],  &whitetree[84],  NOTTERMINAL},
/* 054 */     {&blacktree[1],   &blacktree[2],   13},
/* 055 */     {&whitetree[85],  &whitetree[86],  NOTTERMINAL},
/* 056 */     {&whitetree[87],  &whitetree[88],  NOTTERMINAL},
/* 057 */     {&whitetree[89],  &whitetree[90],  NOTTERMINAL},
/* 058 */     {&blacktree[1],   &blacktree[2],   1},
/* 059 */     {&blacktree[1],   &blacktree[2],   12},
/* 060 */     {&whitetree[91],  &whitetree[92],  NOTTERMINAL},
/* 061 */     {&whitetree[93],  &whitetree[94],  NOTTERMINAL},
/* 062 */     {&whitetree[95],  &whitetree[96],  NOTTERMINAL},
/* 063 */     {&whitetree[97],  &whitetree[98],  NOTTERMINAL},
/* 064 */     {&whitetree[99],  &whitetree[100], NOTTERMINAL},
/* 065 */     {&whitetree[101], &whitetree[102], NOTTERMINAL},
/* 066 */     {&whitetree[103], &whitetree[104], NOTTERMINAL},
/* 067 */     {&whitetree[105], &whitetree[106], NOTTERMINAL},
/* 068 */     {&whitetree[107], &whitetree[108], NOTTERMINAL},
/* 069 */     {&whitetree[109], &whitetree[110], NOTTERMINAL},
/* 070 */     {&whitetree[1],   &whitetree[2],   192},
/* 071 */     {&whitetree[1],   &whitetree[2],   1664},
/* 072 */     {&whitetree[111], &whitetree[112], NOTTERMINAL},
/* 073 */     {&whitetree[113], &whitetree[114], NOTTERMINAL},
/* 074 */     {&whitetree[115], &whitetree[116], NOTTERMINAL},
/* 075 */     {&blacktree[1],   &blacktree[2],   16},
/* 076 */     {&blacktree[1],   &blacktree[2],   17},
/* 077 */     {&blacktree[1],   &blacktree[2],   14},
/* 078 */     {&blacktree[1],   &blacktree[2],   15},
/* 079 */     {&whitetree[117], &whitetree[118], NOTTERMINAL},
/* 080 */     {&whitetree[119], &whitetree[120], NOTTERMINAL},
/* 081 */     {&whitetree[121], &whitetree[122], NOTTERMINAL},
/* 082 */     {&blacktree[1],   &blacktree[2],   22},
/* 083 */     {&blacktree[1],   &blacktree[2],   23},
/* 084 */     {&whitetree[123], &whitetree[124], NOTTERMINAL},
/* 085 */     {&blacktree[1],   &blacktree[2],   20},
/* 086 */     {&whitetree[125], &whitetree[126], NOTTERMINAL},
/* 087 */     {&whitetree[127], &whitetree[128], NOTTERMINAL},
/* 088 */     {&whitetree[129], &whitetree[130], NOTTERMINAL},
/* 089 */     {&blacktree[1],   &blacktree[2],   19},
/* 090 */     {&whitetree[131], &whitetree[132], NOTTERMINAL},
/* 091 */     {&whitetree[133], &whitetree[134], NOTTERMINAL},
/* 092 */     {&blacktree[1],   &blacktree[2],   26},
/* 093 */     {&whitetree[135], &whitetree[136], NOTTERMINAL},
/* 094 */     {&whitetree[137], &whitetree[138], NOTTERMINAL},
/* 095 */     {&whitetree[139], &whitetree[140], NOTTERMINAL},
/* 096 */     {&blacktree[1],   &blacktree[2],   21},
/* 097 */     {&blacktree[1],   &blacktree[2],   28},
/* 098 */     {&whitetree[141], &whitetree[142], NOTTERMINAL},
/* 099 */     {&whitetree[143], &whitetree[144], NOTTERMINAL},
/* 100 */     {&whitetree[145], &whitetree[146], NOTTERMINAL},
/* 101 */     {&blacktree[1],   &blacktree[2],   27},
/* 102 */     {&whitetree[147], &whitetree[148], NOTTERMINAL},
/* 103 */     {&whitetree[149], &whitetree[150], NOTTERMINAL},
/* 104 */     {&blacktree[1],   &blacktree[2],   18},
/* 105 */     {&blacktree[1],   &blacktree[2],   24},
/* 106 */     {&whitetree[151], &whitetree[152], NOTTERMINAL},
/* 107 */     {&whitetree[153], &whitetree[154], NOTTERMINAL},
/* 108 */     {&blacktree[1],   &blacktree[2],   25},
/* 109 */     {&whitetree[155], &whitetree[156], NOTTERMINAL},
/* 110 */     {&whitetree[157], &whitetree[158], NOTTERMINAL},
/* 111 */     {&whitetree[159], &whitetree[160], NOTTERMINAL},
/* 112 */     {&whitetree[161], &whitetree[162], NOTTERMINAL},
/* 113 */     {&whitetree[163], &whitetree[164], NOTTERMINAL},
/* 114 */     {&whitetree[165], &whitetree[166], NOTTERMINAL},
/* 115 */     {&whitetree[167], &whitetree[168], NOTTERMINAL},
/* 116 */     {&whitetree[1],   &whitetree[2],   256},
/* 117 */     {&whitetree[169], &eoltree[0],    NOTTERMINAL},
/* 118 */     {&whitetree[170], &whitetree[171], NOTTERMINAL},
/* 119 */     {&blacktree[1],   &blacktree[2],   29},
/* 120 */     {&blacktree[1],   &blacktree[2],   30},
/* 121 */     {&blacktree[1],   &blacktree[2],   45},
/* 122 */     {&blacktree[1],   &blacktree[2],   46},
/* 123 */     {&blacktree[1],   &blacktree[2],   47},
/* 124 */     {&blacktree[1],   &blacktree[2],   48},
/* 125 */     {&blacktree[1],   &blacktree[2],   33},
/* 126 */     {&blacktree[1],   &blacktree[2],   34},
/* 127 */     {&blacktree[1],   &blacktree[2],   35},
/* 128 */     {&blacktree[1],   &blacktree[2],   36},
/* 129 */     {&blacktree[1],   &blacktree[2],   37},
/* 130 */     {&blacktree[1],   &blacktree[2],   38},
/* 131 */     {&blacktree[1],   &blacktree[2],   31},
/* 132 */     {&blacktree[1],   &blacktree[2],   32},
/* 133 */     {&blacktree[1],   &blacktree[2],   53},
/* 134 */     {&blacktree[1],   &blacktree[2],   54},
/* 135 */     {&blacktree[1],   &blacktree[2],   39},
/* 136 */     {&blacktree[1],   &blacktree[2],   40},
/* 137 */     {&blacktree[1],   &blacktree[2],   41},
/* 138 */     {&blacktree[1],   &blacktree[2],   42},
/* 139 */     {&blacktree[1],   &blacktree[2],   43},
/* 140 */     {&blacktree[1],   &blacktree[2],   44},
/* 141 */     {&blacktree[1],   &blacktree[2],   61},
/* 142 */     {&blacktree[1],   &blacktree[2],   62},
/* 143 */     {&blacktree[1],   &blacktree[2],   63},
/* 144 */     {&blacktree[1],   &blacktree[2],   0},
/* 145 */     {&whitetree[1],   &whitetree[2],   320},
/* 146 */     {&whitetree[1],   &whitetree[2],   384},
/* 147 */     {&blacktree[1],   &blacktree[2],   59},
/* 148 */     {&blacktree[1],   &blacktree[2],   60},
/* 149 */     {&whitetree[172], &whitetree[173], NOTTERMINAL},
/* 150 */     {&whitetree[174], &whitetree[175], NOTTERMINAL},
/* 151 */     {&blacktree[1],   &blacktree[2],   49},
/* 152 */     {&blacktree[1],   &blacktree[2],   50},
/* 153 */     {&blacktree[1],   &blacktree[2],   51},
/* 154 */     {&blacktree[1],   &blacktree[2],   52},
/* 155 */     {&blacktree[1],   &blacktree[2],   55},
/* 156 */     {&blacktree[1],   &blacktree[2],   56},
/* 157 */     {&blacktree[1],   &blacktree[2],   57},
/* 158 */     {&blacktree[1],   &blacktree[2],   58},
/* 159 */     {&whitetree[1],   &whitetree[2],   448},
/* 160 */     {&whitetree[1],   &whitetree[2],   512},
/* 161 */     {&whitetree[176], &whitetree[177], NOTTERMINAL},
/* 162 */     {&whitetree[1],   &whitetree[2],   640},
/* 163 */     {&whitetree[1],   &whitetree[2],   576},
/* 164 */     {&whitetree[178], &whitetree[179], NOTTERMINAL},
/* 165 */     {&whitetree[180], &whitetree[181], NOTTERMINAL},
/* 166 */     {&whitetree[182], &whitetree[183], NOTTERMINAL},
/* 167 */     {&whitetree[184], &whitetree[185], NOTTERMINAL},
/* 168 */     {&whitetree[186], &whitetree[187], NOTTERMINAL},
/* 169 */     {&whitetree[188], &eoltree[0],    NOTTERMINAL},
/* 170 */     {&whitetree[189], &whitetree[190], NOTTERMINAL},
/* 171 */     {&whitetree[191], &whitetree[192], NOTTERMINAL},
/* 172 */     {&whitetree[1],   &whitetree[2],   1472},
/* 173 */     {&whitetree[1],   &whitetree[2],   1536},
/* 174 */     {&whitetree[1],   &whitetree[2],   1600},
/* 175 */     {&whitetree[1],   &whitetree[2],   1728},
/* 176 */     {&whitetree[1],   &whitetree[2],   704},
/* 177 */     {&whitetree[1],   &whitetree[2],   768},
/* 178 */     {&whitetree[1],   &whitetree[2],   832},
/* 179 */     {&whitetree[1],   &whitetree[2],   896},
/* 180 */     {&whitetree[1],   &whitetree[2],   960},
/* 181 */     {&whitetree[1],   &whitetree[2],   1024},
/* 182 */     {&whitetree[1],   &whitetree[2],   1088},
/* 183 */     {&whitetree[1],   &whitetree[2],   1152},
/* 184 */     {&whitetree[1],   &whitetree[2],   1216},
/* 185 */     {&whitetree[1],   &whitetree[2],   1280},
/* 186 */     {&whitetree[1],   &whitetree[2],   1344},
/* 187 */     {&whitetree[1],   &whitetree[2],   1408},
/* 188 */     {&whitetree[193], &eoltree[0],    NOTTERMINAL},
/* 189 */     {&whitetree[194], &whitetree[195], NOTTERMINAL},
/* 190 */     {&whitetree[196], &whitetree[197], NOTTERMINAL},
/* 191 */     {&whitetree[198], &whitetree[199], NOTTERMINAL},
/* 192 */     {&whitetree[200], &whitetree[201], NOTTERMINAL},
/* 193 */     {&whitetree[193], &whitetree[202], NOTTERMINAL},
/* 194 */     {&whitetree[1],   &whitetree[2],   1792},
/* 195 */     {&whitetree[203], &whitetree[204], NOTTERMINAL},
/* 196 */     {&whitetree[205], &whitetree[206], NOTTERMINAL},
/* 197 */     {&whitetree[207], &whitetree[208], NOTTERMINAL},
/* 198 */     {&whitetree[1],   &whitetree[2],   1856},
/* 199 */     {&whitetree[1],   &whitetree[2],   1920},
/* 200 */     {&whitetree[209], &whitetree[210], NOTTERMINAL},
/* 201 */     {&whitetree[211], &whitetree[212], NOTTERMINAL},
/* 202 */     {&whitetree[1],   &whitetree[2],   EOL_MARKER },
/* 203 */     {&whitetree[1],   &whitetree[2],   1984},
/* 204 */     {&whitetree[1],   &whitetree[2],   2048},
/* 205 */     {&whitetree[1],   &whitetree[2],   2112},
/* 206 */     {&whitetree[1],   &whitetree[2],   2176},
/* 207 */     {&whitetree[1],   &whitetree[2],   2240},
/* 208 */     {&whitetree[1],   &whitetree[2],   2304},
/* 209 */     {&whitetree[1],   &whitetree[2],   2368},
/* 210 */     {&whitetree[1],   &whitetree[2],   2432},
/* 211 */     {&whitetree[1],   &whitetree[2],   2496},
/* 212 */     {&whitetree[1],   &whitetree[2],   2560},
};

T4NODE blacktree[] = {
/* 000 */     {&blacktree[1],   &blacktree[2],   NOTTERMINAL},
/* 001 */     {&blacktree[3],   &blacktree[4],   NOTTERMINAL},
/* 002 */     {&blacktree[5],   &blacktree[6],   NOTTERMINAL},
/* 003 */     {&blacktree[7],   &blacktree[8],   NOTTERMINAL},
/* 004 */     {&blacktree[9],   &blacktree[10],  NOTTERMINAL},
/* 005 */     {&whitetree[1],   &whitetree[2],   3},
/* 006 */     {&whitetree[1],   &whitetree[2],   2},
/* a */     {&blacktree[11],  &blacktree[12],  NOTTERMINAL},
/* 008 */     {&blacktree[13],  &blacktree[14],  NOTTERMINAL},
/* 009 */     {&whitetree[1],   &whitetree[2],   1},
/* 010 */     {&whitetree[1],   &whitetree[2],   4},
/* 011 */     {&blacktree[15],  &blacktree[16],  NOTTERMINAL},
/* 012 */     {&blacktree[17],  &blacktree[18],  NOTTERMINAL},
/* 013 */     {&whitetree[1],   &whitetree[2],   6},
/* 014 */     {&whitetree[1],   &whitetree[2],   5},
/* 015 */     {&blacktree[19],  &blacktree[20],  NOTTERMINAL},
/* 016 */     {&blacktree[21],  &blacktree[22],  NOTTERMINAL},
/* 017 */     {&blacktree[23],  &blacktree[24],  NOTTERMINAL},
/* 018 */     {&whitetree[1],   &whitetree[2],   7},
/* 019 */     {&blacktree[25],  &blacktree[26],  NOTTERMINAL},
/* 020 */     {&blacktree[27],  &blacktree[28],  NOTTERMINAL},
/* 021 */     {&blacktree[29],  &blacktree[30],  NOTTERMINAL},
/* 022 */     {&blacktree[31],  &blacktree[32],  NOTTERMINAL},
/* 023 */     {&whitetree[1],   &whitetree[2],   9},
/* 024 */     {&whitetree[1],   &whitetree[2],   8},
/* 025 */     {&blacktree[33],  &blacktree[34],  NOTTERMINAL},
/* 026 */     {&blacktree[35],  &blacktree[36],  NOTTERMINAL},
/* 027 */     {&blacktree[37],  &blacktree[38],  NOTTERMINAL},
/* 028 */     {&blacktree[39],  &blacktree[40],  NOTTERMINAL},
/* 029 */     {&whitetree[1],   &whitetree[2],   10},
/* 030 */     {&whitetree[1],   &whitetree[2],   11},
/* 031 */     {&blacktree[41],  &blacktree[42],  NOTTERMINAL},
/* 032 */     {&whitetree[1],   &whitetree[2],   12},
/* 033 */     {&blacktree[43],  &eoltree[0],    NOTTERMINAL},
/* 034 */     {&blacktree[44],  &blacktree[45],  NOTTERMINAL},
/* 035 */     {&blacktree[46],  &blacktree[47],  NOTTERMINAL},
/* 036 */     {&blacktree[48],  &blacktree[49],  NOTTERMINAL},
/* 037 */     {&whitetree[1],   &whitetree[2],   13},
/* 038 */     {&blacktree[50],  &blacktree[51],  NOTTERMINAL},
/* 039 */     {&blacktree[52],  &blacktree[53],  NOTTERMINAL},
/* 040 */     {&whitetree[1],   &whitetree[2],   14},
/* 041 */     {&blacktree[54],  &blacktree[55],  NOTTERMINAL},
/* 042 */     {&blacktree[56],  &blacktree[57],  NOTTERMINAL},
/* 043 */     {&blacktree[58],  &eoltree[0],    NOTTERMINAL},
/* 044 */     {&blacktree[59],  &blacktree[60],  NOTTERMINAL},
/* 045 */     {&blacktree[61],  &blacktree[62],  NOTTERMINAL},
/* 046 */     {&blacktree[63],  &blacktree[64],  NOTTERMINAL},
/* 047 */     {&blacktree[65],  &blacktree[66],  NOTTERMINAL},
/* 048 */     {&blacktree[67],  &blacktree[68],  NOTTERMINAL},
/* 049 */     {&blacktree[69],  &blacktree[70],  NOTTERMINAL},
/* 050 */     {&blacktree[71],  &blacktree[72],  NOTTERMINAL},
/* 051 */     {&blacktree[73],  &blacktree[74],  NOTTERMINAL},
/* 052 */     {&blacktree[75],  &blacktree[76],  NOTTERMINAL},
/* 053 */     {&blacktree[77],  &blacktree[78],  NOTTERMINAL},
/* 054 */     {&whitetree[1],   &whitetree[2],   15},
/* 055 */     {&blacktree[79],  &blacktree[80],  NOTTERMINAL},
/* 056 */     {&blacktree[81],  &blacktree[82],  NOTTERMINAL},
/* 057 */     {&blacktree[83],  &blacktree[84],  NOTTERMINAL},
/* 058 */     {&blacktree[85],  &eoltree[0],    NOTTERMINAL},
/* 059 */     {&blacktree[86],  &blacktree[87],  NOTTERMINAL},
/* 060 */     {&blacktree[88],  &blacktree[89],  NOTTERMINAL},
/* 061 */     {&blacktree[90],  &blacktree[91],  NOTTERMINAL},
/* 062 */     {&blacktree[92],  &blacktree[93],  NOTTERMINAL},
/* 063 */     {&whitetree[1],   &whitetree[2],   18},
/* 064 */     {&blacktree[94],  &blacktree[95],  NOTTERMINAL},
/* 065 */     {&blacktree[96],  &blacktree[97],  NOTTERMINAL},
/* 066 */     {&blacktree[98],  &blacktree[99],  NOTTERMINAL},
/* 067 */     {&blacktree[100], &blacktree[101], NOTTERMINAL},
/* 068 */     {&blacktree[102], &blacktree[103], NOTTERMINAL},
/* 069 */     {&blacktree[104], &blacktree[105], NOTTERMINAL},
/* 070 */     {&blacktree[1],   &blacktree[2],   64},
/* 071 */     {&blacktree[106], &blacktree[107], NOTTERMINAL},
/* 072 */     {&blacktree[108], &blacktree[109], NOTTERMINAL},
/* 073 */     {&blacktree[110], &blacktree[111], NOTTERMINAL},
/* 074 */     {&whitetree[1],   &whitetree[2],   16},
/* 075 */     {&whitetree[1],   &whitetree[2],   17},
/* 076 */     {&blacktree[112], &blacktree[113], NOTTERMINAL},
/* 077 */     {&blacktree[114], &blacktree[115], NOTTERMINAL},
/* 078 */     {&blacktree[116], &blacktree[117], NOTTERMINAL},
/* 079 */     {&blacktree[118], &blacktree[119], NOTTERMINAL},
/* 080 */     {&blacktree[120], &blacktree[121], NOTTERMINAL},
/* 081 */     {&blacktree[122], &blacktree[123], NOTTERMINAL},
/* 082 */     {&blacktree[124], &blacktree[125], NOTTERMINAL},
/* 083 */     {&blacktree[126], &blacktree[127], NOTTERMINAL},
/* 084 */     {&whitetree[1],   &whitetree[2],   0},
/* 085 */     {&blacktree[85],  &blacktree[128], NOTTERMINAL},
/* 086 */     {&blacktree[1],   &blacktree[2],   1792},
/* 087 */     {&blacktree[129], &blacktree[130], NOTTERMINAL},
/* 088 */     {&blacktree[131], &blacktree[132], NOTTERMINAL},
/* 089 */     {&blacktree[133], &blacktree[134], NOTTERMINAL},
/* 090 */     {&blacktree[1],   &blacktree[2],   1856},
/* 091 */     {&blacktree[1],   &blacktree[2],   1920},
/* 092 */     {&blacktree[135], &blacktree[136], NOTTERMINAL},
/* 093 */     {&blacktree[137], &blacktree[138], NOTTERMINAL},
/* 094 */     {&blacktree[139], &blacktree[140], NOTTERMINAL},
/* 095 */     {&blacktree[141], &blacktree[142], NOTTERMINAL},
/* 096 */     {&blacktree[143], &blacktree[144], NOTTERMINAL},
/* 097 */     {&blacktree[145], &blacktree[146], NOTTERMINAL},
/* 098 */     {&blacktree[147], &blacktree[148], NOTTERMINAL},
/* 099 */     {&whitetree[1],   &whitetree[2],   24},
/* 100 */     {&whitetree[1],   &whitetree[2],   25},
/* 101 */     {&blacktree[149], &blacktree[150], NOTTERMINAL},
/* 102 */     {&blacktree[151], &blacktree[152], NOTTERMINAL},
/* 103 */     {&blacktree[153], &blacktree[154], NOTTERMINAL},
/* 104 */     {&blacktree[155], &blacktree[156], NOTTERMINAL},
/* 105 */     {&blacktree[157], &blacktree[158], NOTTERMINAL},
/* 106 */     {&whitetree[1],   &whitetree[2],   23},
/* 107 */     {&blacktree[159], &blacktree[160], NOTTERMINAL},
/* 108 */     {&blacktree[161], &blacktree[162], NOTTERMINAL},
/* 109 */     {&blacktree[163], &blacktree[164], NOTTERMINAL},
/* 110 */     {&blacktree[165], &blacktree[166], NOTTERMINAL},
/* 111 */     {&blacktree[167], &blacktree[168], NOTTERMINAL},
/* 112 */     {&blacktree[169], &blacktree[170], NOTTERMINAL},
/* 113 */     {&blacktree[171], &blacktree[172], NOTTERMINAL},
/* 114 */     {&blacktree[173], &blacktree[174], NOTTERMINAL},
/* 115 */     {&blacktree[175], &blacktree[176], NOTTERMINAL},
/* 116 */     {&blacktree[177], &blacktree[178], NOTTERMINAL},
/* 117 */     {&whitetree[1],   &whitetree[2],   22},
/* 118 */     {&blacktree[179], &blacktree[180], NOTTERMINAL},
/* 119 */     {&blacktree[181], &blacktree[182], NOTTERMINAL},
/* 120 */     {&blacktree[183], &blacktree[184], NOTTERMINAL},
/* 121 */     {&whitetree[1],   &whitetree[2],   19},
/* 122 */     {&whitetree[1],   &whitetree[2],   20},
/* 123 */     {&blacktree[185], &blacktree[186], NOTTERMINAL},
/* 124 */     {&blacktree[187], &blacktree[188], NOTTERMINAL},
/* 125 */     {&blacktree[189], &blacktree[190], NOTTERMINAL},
/* 126 */     {&whitetree[1],   &whitetree[2],   21},
/* 127 */     {&blacktree[191], &blacktree[192], NOTTERMINAL},
/* 128 */     {&whitetree[1],   &whitetree[2],   EOL_MARKER},
/* 129 */     {&blacktree[1],   &blacktree[2],   1984},
/* 130 */     {&blacktree[1],   &blacktree[2],   2048},
/* 131 */     {&blacktree[1],   &blacktree[2],   2112},
/* 132 */     {&blacktree[1],   &blacktree[2],   2176},
/* 133 */     {&blacktree[1],   &blacktree[2],   2240},
/* 134 */     {&blacktree[1],   &blacktree[2],   2304},
/* 135 */     {&blacktree[1],   &blacktree[2],   2368},
/* 136 */     {&blacktree[1],   &blacktree[2],   2432},
/* 137 */     {&blacktree[1],   &blacktree[2],   2496},
/* 138 */     {&blacktree[1],   &blacktree[2],   2560},
/* 139 */     {&whitetree[1],   &whitetree[2],   52},
/* 140 */     {&blacktree[193], &blacktree[194], NOTTERMINAL},
/* 141 */     {&blacktree[195], &blacktree[196], NOTTERMINAL},
/* 142 */     {&whitetree[1],   &whitetree[2],   55},
/* 143 */     {&whitetree[1],   &whitetree[2],   56},
/* 144 */     {&blacktree[197], &blacktree[198], NOTTERMINAL},
/* 145 */     {&blacktree[199], &blacktree[200], NOTTERMINAL},
/* 146 */     {&whitetree[1],   &whitetree[2],   59},
/* 147 */     {&whitetree[1],   &whitetree[2],   60},
/* 148 */     {&blacktree[201], &blacktree[202], NOTTERMINAL},
/* 149 */     {&blacktree[203], &blacktree[204], NOTTERMINAL},
/* 150 */     {&blacktree[1],   &blacktree[2],   320},
/* 151 */     {&blacktree[1],   &blacktree[2],   384},
/* 152 */     {&blacktree[1],   &blacktree[2],   448},
/* 153 */     {&blacktree[205], &blacktree[206], NOTTERMINAL},
/* 154 */     {&whitetree[1],   &whitetree[2],   53},
/* 155 */     {&whitetree[1],   &whitetree[2],   54},
/* 156 */     {&blacktree[207], &blacktree[208], NOTTERMINAL},
/* 157 */     {&blacktree[209], &blacktree[210], NOTTERMINAL},
/* 158 */     {&blacktree[211], &blacktree[212], NOTTERMINAL},
/* 159 */     {&whitetree[1],   &whitetree[2],   50},
/* 160 */     {&whitetree[1],   &whitetree[2],   51},
/* 161 */     {&whitetree[1],   &whitetree[2],   44},
/* 162 */     {&whitetree[1],   &whitetree[2],   45},
/* 163 */     {&whitetree[1],   &whitetree[2],   46},
/* 164 */     {&whitetree[1],   &whitetree[2],   47},
/* 165 */     {&whitetree[1],   &whitetree[2],   57},
/* 166 */     {&whitetree[1],   &whitetree[2],   58},
/* 167 */     {&whitetree[1],   &whitetree[2],   61},
/* 168 */     {&blacktree[1],   &blacktree[2],   256},
/* 169 */     {&whitetree[1],   &whitetree[2],   48},
/* 170 */     {&whitetree[1],   &whitetree[2],   49},
/* 171 */     {&whitetree[1],   &whitetree[2],   62},
/* 172 */     {&whitetree[1],   &whitetree[2],   63},
/* 173 */     {&whitetree[1],   &whitetree[2],   30},
/* 174 */     {&whitetree[1],   &whitetree[2],   31},
/* 175 */     {&whitetree[1],   &whitetree[2],   32},
/* 176 */     {&whitetree[1],   &whitetree[2],   33},
/* 177 */     {&whitetree[1],   &whitetree[2],   40},
/* 178 */     {&whitetree[1],   &whitetree[2],   41},
/* 179 */     {&blacktree[1],   &blacktree[2],   128},
/* 180 */     {&blacktree[1],   &blacktree[2],   192},
/* 181 */     {&whitetree[1],   &whitetree[2],   26},
/* 182 */     {&whitetree[1],   &whitetree[2],   27},
/* 183 */     {&whitetree[1],   &whitetree[2],   28},
/* 184 */     {&whitetree[1],   &whitetree[2],   29},
/* 185 */     {&whitetree[1],   &whitetree[2],   34},
/* 186 */     {&whitetree[1],   &whitetree[2],   35},
/* 187 */     {&whitetree[1],   &whitetree[2],   36},
/* 188 */     {&whitetree[1],   &whitetree[2],   37},
/* 189 */     {&whitetree[1],   &whitetree[2],   38},
/* 190 */     {&whitetree[1],   &whitetree[2],   39},
/* 191 */     {&whitetree[1],   &whitetree[2],   42},
/* 192 */     {&whitetree[1],   &whitetree[2],   43},
/* 193 */     {&blacktree[1],   &blacktree[2],   640},
/* 194 */     {&blacktree[1],   &blacktree[2],   704},
/* 195 */     {&blacktree[1],   &blacktree[2],   768},
/* 196 */     {&blacktree[1],   &blacktree[2],   832},
/* 197 */     {&blacktree[1],   &blacktree[2],   1280},
/* 198 */     {&blacktree[1],   &blacktree[2],   1344},
/* 199 */     {&blacktree[1],   &blacktree[2],   1408},
/* 200 */     {&blacktree[1],   &blacktree[2],   1472},
/* 201 */     {&blacktree[1],   &blacktree[2],   1536},
/* 202 */     {&blacktree[1],   &blacktree[2],   1600},
/* 203 */     {&blacktree[1],   &blacktree[2],   1664},
/* 204 */     {&blacktree[1],   &blacktree[2],   1728},
/* 205 */     {&blacktree[1],   &blacktree[2],   512},
/* 206 */     {&blacktree[1],   &blacktree[2],   576},
/* 207 */     {&blacktree[1],   &blacktree[2],   896},
/* 208 */     {&blacktree[1],   &blacktree[2],   960},
/* 209 */     {&blacktree[1],   &blacktree[2],   1024},
/* 210 */     {&blacktree[1],   &blacktree[2],   1088},
/* 211 */     {&blacktree[1],   &blacktree[2],   1152},
/* 212 */     {&blacktree[1],   &blacktree[2],   1216},
};



T4NODE eoltree[] = {
/* 000 */     {&eoltree[1],    &eoltree[0],    NOTTERMINAL},
/* 001 */     {&eoltree[2],    &eoltree[0],    NOTTERMINAL},
/* 002 */     {&eoltree[3],    &eoltree[0],    NOTTERMINAL},
/* 003 */     {&eoltree[4],    &eoltree[0],    NOTTERMINAL},
/* 004 */     {&eoltree[5],    &eoltree[0],    NOTTERMINAL},
/* 005 */     {&eoltree[6],    &eoltree[0],    NOTTERMINAL},
/* 006 */     {&eoltree[7],    &eoltree[0],    NOTTERMINAL},
/* a */     {&eoltree[8],    &eoltree[0],    NOTTERMINAL},
/* 008 */     {&eoltree[9],    &eoltree[0],    NOTTERMINAL},
/* 009 */     {&eoltree[10],   &eoltree[0],    NOTTERMINAL},
/* 010 */     {&eoltree[11],   &eoltree[0],    NOTTERMINAL},
/* 011 */     {&eoltree[11],   &eoltree[12],   NOTTERMINAL},
/* 012 */     {&whitetree[1],   &whitetree[2],   EOL_MARKER}
};

#ifdef NO_EOL_OUTPUT

T4NODE _eoltree[] = {
/* 000 */     {&_eoltree[1],     &_eoltree[0],     NOTTERMINAL},
/* 001 */     {&_eoltree[2],     &_eoltree[0],     NOTTERMINAL},
/* 002 */     {&_eoltree[3],     &_eoltree[0],     NOTTERMINAL},
/* 003 */     {&_eoltree[4],     &_eoltree[0],     NOTTERMINAL},
/* 004 */     {&_eoltree[5],     &_eoltree[0],     NOTTERMINAL},
/* 005 */     {&_eoltree[6],     &_eoltree[0],     NOTTERMINAL},
/* 006 */     {&_eoltree[7],     &_eoltree[0],     NOTTERMINAL},
/* a */     {&_eoltree[8],     &_eoltree[0],     NOTTERMINAL},
/* 008 */     {&_eoltree[9],     &_eoltree[0],     NOTTERMINAL},
/* 009 */     {&_eoltree[10],    &_eoltree[0],     NOTTERMINAL},
/* 010 */     {&_eoltree[11],    &_eoltree[0],     NOTTERMINAL},
/* 011 */     {&_eoltree[11],    &_eoltree[12],    NOTTERMINAL},
/* 012 */     {&whitetree[1],   &whitetree[2],   NOTTERMINAL}
};
T4NODE starttree[] = {
/* 000 */     {&starttree[0],   &starttree[1],   NOTTERMINAL},
/* 001 */     {&whitetree[1],   &whitetree[2],   NOTTERMINAL}
};

#endif
