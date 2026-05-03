static const char rootContent[] PROGMEM =
R"==(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>WordClock Setup</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    :root {
      --bg: #f2efe9;
      --card: #fff;
      --txt: #1c1c1c;
      --sub: #888;
      --acc: #5c7a42;
      --acc2: #496233;
      --bdr: #e6e2db;
      --r: 14px;
    }
    * { box-sizing: border-box; margin: 0; padding: 0; }
    body {
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Helvetica, sans-serif;
      background: var(--bg);
      color: var(--txt);
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 16px;
    }
    .card {
      background: var(--card);
      border-radius: var(--r);
      box-shadow: 0 4px 32px rgba(0,0,0,.09);
      width: 100%;
      max-width: 400px;
    }
    .steps {
      display: flex;
      gap: 5px;
      padding: 22px 22px 0;
    }
    .dot {
      height: 5px;
      border-radius: 3px;
      background: var(--bdr);
      transition: all .3s ease;
    }
    .dot.active { flex: 2.5; background: var(--acc); }
    .dot.done   { flex: 1;   background: var(--acc); opacity: .35; }
    .dot.idle   { flex: 1; }
    .panel { display: none; padding: 26px 22px 6px; }
    .panel.active { display: block; }
    h2 { font-size: 19px; font-weight: 600; margin-bottom: 3px; }
    .sub { font-size: 13px; color: var(--sub); margin-bottom: 22px; }
    label {
      display: block;
      font-size: 11px;
      font-weight: 600;
      text-transform: uppercase;
      letter-spacing: .6px;
      color: var(--sub);
      margin-bottom: 6px;
    }
    select, input[type=date], input[type=file] {
      width: 100%;
      padding: 9px 11px;
      border: 1.5px solid var(--bdr);
      border-radius: 8px;
      font: 15px/1 inherit;
      color: var(--txt);
      background: var(--card);
      outline: none;
      transition: border-color .2s;
      appearance: none;
    }
    select:focus, input:focus { border-color: var(--acc); }
    select {
      background-image: url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='10' height='6'%3E%3Cpath d='M0 0l5 6 5-6z' fill='%23999'/%3E%3C/svg%3E");
      background-repeat: no-repeat;
      background-position: right 12px center;
      padding-right: 30px;
    }
    #bday-list { display: flex; flex-direction: column; gap: 8px; }
    .brow { display: flex; gap: 8px; align-items: center; }
    .brow input { flex: 1; }
    .rm {
      background: none;
      border: none;
      color: var(--sub);
      cursor: pointer;
      font-size: 17px;
      line-height: 1;
      padding: 3px 4px;
    }
    .rm:hover { color: #c00; }
    .add-btn {
      width: 100%;
      padding: 9px;
      margin-top: 8px;
      border: 1.5px dashed var(--bdr);
      border-radius: 8px;
      background: none;
      color: var(--sub);
      font: 13px inherit;
      cursor: pointer;
      transition: all .2s;
    }
    .add-btn:hover { border-color: var(--acc); color: var(--acc); }
    .prog-wrap { margin-top: 14px; display: none; }
    .prog-bar { height: 5px; background: var(--bdr); border-radius: 3px; overflow: hidden; }
    .prog-fill { height: 100%; width: 0; background: var(--acc); transition: width .15s; }
    .prog-pct { font-size: 12px; color: var(--sub); margin-top: 5px; }
    .nav {
      display: flex;
      justify-content: space-between;
      align-items: center;
      padding: 18px 22px 22px;
      margin-top: 18px;
      border-top: 1px solid var(--bdr);
    }
    .btn {
      padding: 9px 20px;
      border-radius: 8px;
      font: 500 14px inherit;
      cursor: pointer;
      border: none;
      transition: all .2s;
    }
    .ghost { background: none; color: var(--sub); }
    .ghost:hover { color: var(--txt); }
    .primary { background: var(--acc); color: #fff; }
    .primary:hover { background: var(--acc2); }
  </style>
</head>
<body>
<div class="card">
  <div class="steps">
    <div class="dot active" id="d0"></div>
    <div class="dot idle"   id="d1"></div>
    <div class="dot idle"   id="d2"></div>
  </div>

  <div class="panel active" id="p0">
    <h2>Timezone</h2>
    <p class="sub">Choose your local timezone</p>
    <label for="tz">Timezone</label>
    <select id="tz"></select>
  </div>

  <div class="panel" id="p1">
    <h2>Birthdays</h2>
    <p class="sub">Dates to celebrate &mdash; optional</p>
    <div id="bday-list"></div>
    <button class="add-btn" id="add-bday">+ Add a birthday</button>
  </div>

  <div class="panel" id="p2">
    <h2>Firmware</h2>
    <p class="sub">Upload a .bin file to update &mdash; optional</p>
    <label for="ota">Firmware file</label>
    <input type="file" id="ota" accept=".bin">
    <div class="prog-wrap" id="prog-wrap">
      <div class="prog-bar"><div class="prog-fill" id="prog-fill"></div></div>
      <div class="prog-pct" id="prog-pct"></div>
    </div>
  </div>

  <div class="nav">
    <button class="btn ghost" id="btn-back" onclick="go(-1)" style="visibility:hidden">Back</button>
    <button class="btn primary" id="btn-next" onclick="go(1)">Continue</button>
  </div>
</div>

<script>
const TZ = {
    "Africa/Abidjan": "GMT0",
    "Africa/Accra": "GMT0",
    "Africa/Addis_Ababa": "EAT-3",
    "Africa/Algiers": "CET-1",
    "Africa/Asmara": "EAT-3",
    "Africa/Bamako": "GMT0",
    "Africa/Bangui": "WAT-1",
    "Africa/Banjul": "GMT0",
    "Africa/Bissau": "GMT0",
    "Africa/Blantyre": "CAT-2",
    "Africa/Brazzaville": "WAT-1",
    "Africa/Bujumbura": "CAT-2",
    "Africa/Cairo": "EET-2",
    "Africa/Casablanca": "<+01>-1",
    "Africa/Ceuta": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Africa/Conakry": "GMT0",
    "Africa/Dakar": "GMT0",
    "Africa/Dar_es_Salaam": "EAT-3",
    "Africa/Djibouti": "EAT-3",
    "Africa/Douala": "WAT-1",
    "Africa/El_Aaiun": "<+01>-1",
    "Africa/Freetown": "GMT0",
    "Africa/Gaborone": "CAT-2",
    "Africa/Harare": "CAT-2",
    "Africa/Johannesburg": "SAST-2",
    "Africa/Juba": "EAT-3",
    "Africa/Kampala": "EAT-3",
    "Africa/Khartoum": "CAT-2",
    "Africa/Kigali": "CAT-2",
    "Africa/Kinshasa": "WAT-1",
    "Africa/Lagos": "WAT-1",
    "Africa/Libreville": "WAT-1",
    "Africa/Lome": "GMT0",
    "Africa/Luanda": "WAT-1",
    "Africa/Lubumbashi": "CAT-2",
    "Africa/Lusaka": "CAT-2",
    "Africa/Malabo": "WAT-1",
    "Africa/Maputo": "CAT-2",
    "Africa/Maseru": "SAST-2",
    "Africa/Mbabane": "SAST-2",
    "Africa/Mogadishu": "EAT-3",
    "Africa/Monrovia": "GMT0",
    "Africa/Nairobi": "EAT-3",
    "Africa/Ndjamena": "WAT-1",
    "Africa/Niamey": "WAT-1",
    "Africa/Nouakchott": "GMT0",
    "Africa/Ouagadougou": "GMT0",
    "Africa/Porto-Novo": "WAT-1",
    "Africa/Sao_Tome": "GMT0",
    "Africa/Tripoli": "EET-2",
    "Africa/Tunis": "CET-1",
    "Africa/Windhoek": "CAT-2",
    "America/Adak": "HST10HDT,M3.2.0,M11.1.0",
    "America/Anchorage": "AKST9AKDT,M3.2.0,M11.1.0",
    "America/Anguilla": "AST4",
    "America/Antigua": "AST4",
    "America/Araguaina": "<-03>3",
    "America/Argentina/Buenos_Aires": "<-03>3",
    "America/Argentina/Catamarca": "<-03>3",
    "America/Argentina/Cordoba": "<-03>3",
    "America/Argentina/Jujuy": "<-03>3",
    "America/Argentina/La_Rioja": "<-03>3",
    "America/Argentina/Mendoza": "<-03>3",
    "America/Argentina/Rio_Gallegos": "<-03>3",
    "America/Argentina/Salta": "<-03>3",
    "America/Argentina/San_Juan": "<-03>3",
    "America/Argentina/San_Luis": "<-03>3",
    "America/Argentina/Tucuman": "<-03>3",
    "America/Argentina/Ushuaia": "<-03>3",
    "America/Aruba": "AST4",
    "America/Asuncion": "<-04>4<-03>,M10.1.0/0,M3.4.0/0",
    "America/Atikokan": "EST5",
    "America/Bahia": "<-03>3",
    "America/Bahia_Banderas": "CST6CDT,M4.1.0,M10.5.0",
    "America/Barbados": "AST4",
    "America/Belem": "<-03>3",
    "America/Belize": "CST6",
    "America/Blanc-Sablon": "AST4",
    "America/Boa_Vista": "<-04>4",
    "America/Bogota": "<-05>5",
    "America/Boise": "MST7MDT,M3.2.0,M11.1.0",
    "America/Cambridge_Bay": "MST7MDT,M3.2.0,M11.1.0",
    "America/Campo_Grande": "<-04>4",
    "America/Cancun": "EST5",
    "America/Caracas": "<-04>4",
    "America/Cayenne": "<-03>3",
    "America/Cayman": "EST5",
    "America/Chicago": "CST6CDT,M3.2.0,M11.1.0",
    "America/Chihuahua": "MST7MDT,M4.1.0,M10.5.0",
    "America/Costa_Rica": "CST6",
    "America/Creston": "MST7",
    "America/Cuiaba": "<-04>4",
    "America/Curacao": "AST4",
    "America/Danmarkshavn": "GMT0",
    "America/Dawson": "MST7",
    "America/Dawson_Creek": "MST7",
    "America/Denver": "MST7MDT,M3.2.0,M11.1.0",
    "America/Detroit": "EST5EDT,M3.2.0,M11.1.0",
    "America/Dominica": "AST4",
    "America/Edmonton": "MST7MDT,M3.2.0,M11.1.0",
    "America/Eirunepe": "<-05>5",
    "America/El_Salvador": "CST6",
    "America/Fort_Nelson": "MST7",
    "America/Fortaleza": "<-03>3",
    "America/Glace_Bay": "AST4ADT,M3.2.0,M11.1.0",
    "America/Godthab": "<-03>3<-02>,M3.5.0/-2,M10.5.0/-1",
    "America/Goose_Bay": "AST4ADT,M3.2.0,M11.1.0",
    "America/Grand_Turk": "EST5EDT,M3.2.0,M11.1.0",
    "America/Grenada": "AST4",
    "America/Guadeloupe": "AST4",
    "America/Guatemala": "CST6",
    "America/Guayaquil": "<-05>5",
    "America/Guyana": "<-04>4",
    "America/Halifax": "AST4ADT,M3.2.0,M11.1.0",
    "America/Havana": "CST5CDT,M3.2.0/0,M11.1.0/1",
    "America/Hermosillo": "MST7",
    "America/Indiana/Indianapolis": "EST5EDT,M3.2.0,M11.1.0",
    "America/Indiana/Knox": "CST6CDT,M3.2.0,M11.1.0",
    "America/Indiana/Marengo": "EST5EDT,M3.2.0,M11.1.0",
    "America/Indiana/Petersburg": "EST5EDT,M3.2.0,M11.1.0",
    "America/Indiana/Tell_City": "CST6CDT,M3.2.0,M11.1.0",
    "America/Indiana/Vevay": "EST5EDT,M3.2.0,M11.1.0",
    "America/Indiana/Vincennes": "EST5EDT,M3.2.0,M11.1.0",
    "America/Indiana/Winamac": "EST5EDT,M3.2.0,M11.1.0",
    "America/Inuvik": "MST7MDT,M3.2.0,M11.1.0",
    "America/Iqaluit": "EST5EDT,M3.2.0,M11.1.0",
    "America/Jamaica": "EST5",
    "America/Juneau": "AKST9AKDT,M3.2.0,M11.1.0",
    "America/Kentucky/Louisville": "EST5EDT,M3.2.0,M11.1.0",
    "America/Kentucky/Monticello": "EST5EDT,M3.2.0,M11.1.0",
    "America/Kralendijk": "AST4",
    "America/La_Paz": "<-04>4",
    "America/Lima": "<-05>5",
    "America/Los_Angeles": "PST8PDT,M3.2.0,M11.1.0",
    "America/Lower_Princes": "AST4",
    "America/Maceio": "<-03>3",
    "America/Managua": "CST6",
    "America/Manaus": "<-04>4",
    "America/Marigot": "AST4",
    "America/Martinique": "AST4",
    "America/Matamoros": "CST6CDT,M3.2.0,M11.1.0",
    "America/Mazatlan": "MST7MDT,M4.1.0,M10.5.0",
    "America/Menominee": "CST6CDT,M3.2.0,M11.1.0",
    "America/Merida": "CST6CDT,M4.1.0,M10.5.0",
    "America/Metlakatla": "AKST9AKDT,M3.2.0,M11.1.0",
    "America/Mexico_City": "CST6CDT,M4.1.0,M10.5.0",
    "America/Miquelon": "<-03>3<-02>,M3.2.0,M11.1.0",
    "America/Moncton": "AST4ADT,M3.2.0,M11.1.0",
    "America/Monterrey": "CST6CDT,M4.1.0,M10.5.0",
    "America/Montevideo": "<-03>3",
    "America/Montreal": "EST5EDT,M3.2.0,M11.1.0",
    "America/Montserrat": "AST4",
    "America/Nassau": "EST5EDT,M3.2.0,M11.1.0",
    "America/New_York": "EST5EDT,M3.2.0,M11.1.0",
    "America/Nipigon": "EST5EDT,M3.2.0,M11.1.0",
    "America/Nome": "AKST9AKDT,M3.2.0,M11.1.0",
    "America/Noronha": "<-02>2",
    "America/North_Dakota/Beulah": "CST6CDT,M3.2.0,M11.1.0",
    "America/North_Dakota/Center": "CST6CDT,M3.2.0,M11.1.0",
    "America/North_Dakota/New_Salem": "CST6CDT,M3.2.0,M11.1.0",
    "America/Nuuk": "<-03>3<-02>,M3.5.0/-2,M10.5.0/-1",
    "America/Ojinaga": "MST7MDT,M3.2.0,M11.1.0",
    "America/Panama": "EST5",
    "America/Pangnirtung": "EST5EDT,M3.2.0,M11.1.0",
    "America/Paramaribo": "<-03>3",
    "America/Phoenix": "MST7",
    "America/Port-au-Prince": "EST5EDT,M3.2.0,M11.1.0",
    "America/Port_of_Spain": "AST4",
    "America/Porto_Velho": "<-04>4",
    "America/Puerto_Rico": "AST4",
    "America/Punta_Arenas": "<-03>3",
    "America/Rainy_River": "CST6CDT,M3.2.0,M11.1.0",
    "America/Rankin_Inlet": "CST6CDT,M3.2.0,M11.1.0",
    "America/Recife": "<-03>3",
    "America/Regina": "CST6",
    "America/Resolute": "CST6CDT,M3.2.0,M11.1.0",
    "America/Rio_Branco": "<-05>5",
    "America/Santarem": "<-03>3",
    "America/Santiago": "<-04>4<-03>,M9.1.6/24,M4.1.6/24",
    "America/Santo_Domingo": "AST4",
    "America/Sao_Paulo": "<-03>3",
    "America/Scoresbysund": "<-01>1<+00>,M3.5.0/0,M10.5.0/1",
    "America/Sitka": "AKST9AKDT,M3.2.0,M11.1.0",
    "America/St_Barthelemy": "AST4",
    "America/St_Johns": "NST3:30NDT,M3.2.0,M11.1.0",
    "America/St_Kitts": "AST4",
    "America/St_Lucia": "AST4",
    "America/St_Thomas": "AST4",
    "America/St_Vincent": "AST4",
    "America/Swift_Current": "CST6",
    "America/Tegucigalpa": "CST6",
    "America/Thule": "AST4ADT,M3.2.0,M11.1.0",
    "America/Thunder_Bay": "EST5EDT,M3.2.0,M11.1.0",
    "America/Tijuana": "PST8PDT,M3.2.0,M11.1.0",
    "America/Toronto": "EST5EDT,M3.2.0,M11.1.0",
    "America/Tortola": "AST4",
    "America/Vancouver": "PST8PDT,M3.2.0,M11.1.0",
    "America/Whitehorse": "MST7",
    "America/Winnipeg": "CST6CDT,M3.2.0,M11.1.0",
    "America/Yakutat": "AKST9AKDT,M3.2.0,M11.1.0",
    "America/Yellowknife": "MST7MDT,M3.2.0,M11.1.0",
    "Antarctica/Casey": "<+11>-11",
    "Antarctica/Davis": "<+07>-7",
    "Antarctica/DumontDUrville": "<+10>-10",
    "Antarctica/Macquarie": "AEST-10AEDT,M10.1.0,M4.1.0/3",
    "Antarctica/Mawson": "<+05>-5",
    "Antarctica/McMurdo": "NZST-12NZDT,M9.5.0,M4.1.0/3",
    "Antarctica/Palmer": "<-03>3",
    "Antarctica/Rothera": "<-03>3",
    "Antarctica/Syowa": "<+03>-3",
    "Antarctica/Troll": "<+00>0<+02>-2,M3.5.0/1,M10.5.0/3",
    "Antarctica/Vostok": "<+06>-6",
    "Arctic/Longyearbyen": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Asia/Aden": "<+03>-3",
    "Asia/Almaty": "<+06>-6",
    "Asia/Amman": "EET-2EEST,M3.5.4/24,M10.5.5/1",
    "Asia/Anadyr": "<+12>-12",
    "Asia/Aqtau": "<+05>-5",
    "Asia/Aqtobe": "<+05>-5",
    "Asia/Ashgabat": "<+05>-5",
    "Asia/Atyrau": "<+05>-5",
    "Asia/Baghdad": "<+03>-3",
    "Asia/Bahrain": "<+03>-3",
    "Asia/Baku": "<+04>-4",
    "Asia/Bangkok": "<+07>-7",
    "Asia/Barnaul": "<+07>-7",
    "Asia/Beirut": "EET-2EEST,M3.5.0/0,M10.5.0/0",
    "Asia/Bishkek": "<+06>-6",
    "Asia/Brunei": "<+08>-8",
    "Asia/Chita": "<+09>-9",
    "Asia/Choibalsan": "<+08>-8",
    "Asia/Colombo": "<+0530>-5:30",
    "Asia/Damascus": "EET-2EEST,M3.5.5/0,M10.5.5/0",
    "Asia/Dhaka": "<+06>-6",
    "Asia/Dili": "<+09>-9",
    "Asia/Dubai": "<+04>-4",
    "Asia/Dushanbe": "<+05>-5",
    "Asia/Famagusta": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Asia/Gaza": "EET-2EEST,M3.4.4/48,M10.4.4/49",
    "Asia/Hebron": "EET-2EEST,M3.4.4/48,M10.4.4/49",
    "Asia/Ho_Chi_Minh": "<+07>-7",
    "Asia/Hong_Kong": "HKT-8",
    "Asia/Hovd": "<+07>-7",
    "Asia/Irkutsk": "<+08>-8",
    "Asia/Jakarta": "WIB-7",
    "Asia/Jayapura": "WIT-9",
    "Asia/Jerusalem": "IST-2IDT,M3.4.4/26,M10.5.0",
    "Asia/Kabul": "<+0430>-4:30",
    "Asia/Kamchatka": "<+12>-12",
    "Asia/Karachi": "PKT-5",
    "Asia/Kathmandu": "<+0545>-5:45",
    "Asia/Khandyga": "<+09>-9",
    "Asia/Kolkata": "IST-5:30",
    "Asia/Krasnoyarsk": "<+07>-7",
    "Asia/Kuala_Lumpur": "<+08>-8",
    "Asia/Kuching": "<+08>-8",
    "Asia/Kuwait": "<+03>-3",
    "Asia/Macau": "CST-8",
    "Asia/Magadan": "<+11>-11",
    "Asia/Makassar": "WITA-8",
    "Asia/Manila": "PST-8",
    "Asia/Muscat": "<+04>-4",
    "Asia/Nicosia": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Asia/Novokuznetsk": "<+07>-7",
    "Asia/Novosibirsk": "<+07>-7",
    "Asia/Omsk": "<+06>-6",
    "Asia/Oral": "<+05>-5",
    "Asia/Phnom_Penh": "<+07>-7",
    "Asia/Pontianak": "WIB-7",
    "Asia/Pyongyang": "KST-9",
    "Asia/Qatar": "<+03>-3",
    "Asia/Qyzylorda": "<+05>-5",
    "Asia/Riyadh": "<+03>-3",
    "Asia/Sakhalin": "<+11>-11",
    "Asia/Samarkand": "<+05>-5",
    "Asia/Seoul": "KST-9",
    "Asia/Shanghai": "CST-8",
    "Asia/Singapore": "<+08>-8",
    "Asia/Srednekolymsk": "<+11>-11",
    "Asia/Taipei": "CST-8",
    "Asia/Tashkent": "<+05>-5",
    "Asia/Tbilisi": "<+04>-4",
    "Asia/Tehran": "<+0330>-3:30<+0430>,J79/24,J263/24",
    "Asia/Thimphu": "<+06>-6",
    "Asia/Tokyo": "JST-9",
    "Asia/Tomsk": "<+07>-7",
    "Asia/Ulaanbaatar": "<+08>-8",
    "Asia/Urumqi": "<+06>-6",
    "Asia/Ust-Nera": "<+10>-10",
    "Asia/Vientiane": "<+07>-7",
    "Asia/Vladivostok": "<+10>-10",
    "Asia/Yakutsk": "<+09>-9",
    "Asia/Yangon": "<+0630>-6:30",
    "Asia/Yekaterinburg": "<+05>-5",
    "Asia/Yerevan": "<+04>-4",
    "Atlantic/Azores": "<-01>1<+00>,M3.5.0/0,M10.5.0/1",
    "Atlantic/Bermuda": "AST4ADT,M3.2.0,M11.1.0",
    "Atlantic/Canary": "WET0WEST,M3.5.0/1,M10.5.0",
    "Atlantic/Cape_Verde": "<-01>1",
    "Atlantic/Faroe": "WET0WEST,M3.5.0/1,M10.5.0",
    "Atlantic/Madeira": "WET0WEST,M3.5.0/1,M10.5.0",
    "Atlantic/Reykjavik": "GMT0",
    "Atlantic/South_Georgia": "<-02>2",
    "Atlantic/St_Helena": "GMT0",
    "Atlantic/Stanley": "<-03>3",
    "Australia/Adelaide": "ACST-9:30ACDT,M10.1.0,M4.1.0/3",
    "Australia/Brisbane": "AEST-10",
    "Australia/Broken_Hill": "ACST-9:30ACDT,M10.1.0,M4.1.0/3",
    "Australia/Currie": "AEST-10AEDT,M10.1.0,M4.1.0/3",
    "Australia/Darwin": "ACST-9:30",
    "Australia/Eucla": "<+0845>-8:45",
    "Australia/Hobart": "AEST-10AEDT,M10.1.0,M4.1.0/3",
    "Australia/Lindeman": "AEST-10",
    "Australia/Lord_Howe": "<+1030>-10:30<+11>-11,M10.1.0,M4.1.0",
    "Australia/Melbourne": "AEST-10AEDT,M10.1.0,M4.1.0/3",
    "Australia/Perth": "AWST-8",
    "Australia/Sydney": "AEST-10AEDT,M10.1.0,M4.1.0/3",
    "Etc/GMT": "GMT0",
    "Etc/GMT+0": "GMT0",
    "Etc/GMT+1": "<-01>1",
    "Etc/GMT+10": "<-10>10",
    "Etc/GMT+11": "<-11>11",
    "Etc/GMT+12": "<-12>12",
    "Etc/GMT+2": "<-02>2",
    "Etc/GMT+3": "<-03>3",
    "Etc/GMT+4": "<-04>4",
    "Etc/GMT+5": "<-05>5",
    "Etc/GMT+6": "<-06>6",
    "Etc/GMT+7": "<-07>7",
    "Etc/GMT+8": "<-08>8",
    "Etc/GMT+9": "<-09>9",
    "Etc/GMT-0": "GMT0",
    "Etc/GMT-1": "<+01>-1",
    "Etc/GMT-10": "<+10>-10",
    "Etc/GMT-11": "<+11>-11",
    "Etc/GMT-12": "<+12>-12",
    "Etc/GMT-13": "<+13>-13",
    "Etc/GMT-14": "<+14>-14",
    "Etc/GMT-2": "<+02>-2",
    "Etc/GMT-3": "<+03>-3",
    "Etc/GMT-4": "<+04>-4",
    "Etc/GMT-5": "<+05>-5",
    "Etc/GMT-6": "<+06>-6",
    "Etc/GMT-7": "<+07>-7",
    "Etc/GMT-8": "<+08>-8",
    "Etc/GMT-9": "<+09>-9",
    "Etc/GMT0": "GMT0",
    "Etc/Greenwich": "GMT0",
    "Etc/UCT": "UTC0",
    "Etc/UTC": "UTC0",
    "Etc/Universal": "UTC0",
    "Etc/Zulu": "UTC0",
    "Europe/Amsterdam": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Andorra": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Astrakhan": "<+04>-4",
    "Europe/Athens": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Belgrade": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Berlin": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Bratislava": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Brussels": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Bucharest": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Budapest": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Busingen": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Chisinau": "EET-2EEST,M3.5.0,M10.5.0/3",
    "Europe/Copenhagen": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Dublin": "IST-1GMT0,M10.5.0,M3.5.0/1",
    "Europe/Gibraltar": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Guernsey": "GMT0BST,M3.5.0/1,M10.5.0",
    "Europe/Helsinki": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Isle_of_Man": "GMT0BST,M3.5.0/1,M10.5.0",
    "Europe/Istanbul": "<+03>-3",
    "Europe/Jersey": "GMT0BST,M3.5.0/1,M10.5.0",
    "Europe/Kaliningrad": "EET-2",
    "Europe/Kiev": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Kirov": "<+03>-3",
    "Europe/Lisbon": "WET0WEST,M3.5.0/1,M10.5.0",
    "Europe/Ljubljana": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/London": "GMT0BST,M3.5.0/1,M10.5.0",
    "Europe/Luxembourg": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Madrid": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Malta": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Mariehamn": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Minsk": "<+03>-3",
    "Europe/Monaco": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Moscow": "MSK-3",
    "Europe/Oslo": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Paris": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Podgorica": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Prague": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Riga": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Rome": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Samara": "<+04>-4",
    "Europe/San_Marino": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Sarajevo": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Saratov": "<+04>-4",
    "Europe/Simferopol": "MSK-3",
    "Europe/Skopje": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Sofia": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Stockholm": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Tallinn": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Tirane": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Ulyanovsk": "<+04>-4",
    "Europe/Uzhgorod": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Vaduz": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Vatican": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Vienna": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Vilnius": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Volgograd": "<+03>-3",
    "Europe/Warsaw": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Zagreb": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Europe/Zaporozhye": "EET-2EEST,M3.5.0/3,M10.5.0/4",
    "Europe/Zurich": "CET-1CEST,M3.5.0,M10.5.0/3",
    "Indian/Antananarivo": "EAT-3",
    "Indian/Chagos": "<+06>-6",
    "Indian/Christmas": "<+07>-7",
    "Indian/Cocos": "<+0630>-6:30",
    "Indian/Comoro": "EAT-3",
    "Indian/Kerguelen": "<+05>-5",
    "Indian/Mahe": "<+04>-4",
    "Indian/Maldives": "<+05>-5",
    "Indian/Mauritius": "<+04>-4",
    "Indian/Mayotte": "EAT-3",
    "Indian/Reunion": "<+04>-4",
    "Pacific/Apia": "<+13>-13<+14>,M9.5.0/3,M4.1.0/4",
    "Pacific/Auckland": "NZST-12NZDT,M9.5.0,M4.1.0/3",
    "Pacific/Bougainville": "<+11>-11",
    "Pacific/Chatham": "<+1245>-12:45<+1345>,M9.5.0/2:45,M4.1.0/3:45",
    "Pacific/Chuuk": "<+10>-10",
    "Pacific/Easter": "<-06>6<-05>,M9.1.6/22,M4.1.6/22",
    "Pacific/Efate": "<+11>-11",
    "Pacific/Enderbury": "<+13>-13",
    "Pacific/Fakaofo": "<+13>-13",
    "Pacific/Fiji": "<+12>-12<+13>,M11.2.0,M1.2.3/99",
    "Pacific/Funafuti": "<+12>-12",
    "Pacific/Galapagos": "<-06>6",
    "Pacific/Gambier": "<-09>9",
    "Pacific/Guadalcanal": "<+11>-11",
    "Pacific/Guam": "ChST-10",
    "Pacific/Honolulu": "HST10",
    "Pacific/Kiritimati": "<+14>-14",
    "Pacific/Kosrae": "<+11>-11",
    "Pacific/Kwajalein": "<+12>-12",
    "Pacific/Majuro": "<+12>-12",
    "Pacific/Marquesas": "<-0930>9:30",
    "Pacific/Midway": "SST11",
    "Pacific/Nauru": "<+12>-12",
    "Pacific/Niue": "<-11>11",
    "Pacific/Norfolk": "<+11>-11<+12>,M10.1.0,M4.1.0/3",
    "Pacific/Noumea": "<+11>-11",
    "Pacific/Pago_Pago": "SST11",
    "Pacific/Palau": "<+09>-9",
    "Pacific/Pitcairn": "<-08>8",
    "Pacific/Pohnpei": "<+11>-11",
    "Pacific/Port_Moresby": "<+10>-10",
    "Pacific/Rarotonga": "<-10>10",
    "Pacific/Saipan": "ChST-10",
    "Pacific/Tahiti": "<-10>10",
    "Pacific/Tarawa": "<+12>-12",
    "Pacific/Tongatapu": "<+13>-13",
    "Pacific/Wake": "<+12>-12",
    "Pacific/Wallis": "<+12>-12"
};

let step = 0;
const N = 3;

function go(dir) {
  if (dir > 0 && step === N - 1) { finish(); return; }
  step = Math.max(0, Math.min(N - 1, step + dir));
  render();
}

function render() {
  for (let i = 0; i < N; i++) {
    document.getElementById('p' + i).className = 'panel' + (i === step ? ' active' : '');
    document.getElementById('d' + i).className = 'dot ' + (i === step ? 'active' : i < step ? 'done' : 'idle');
  }
  document.getElementById('btn-back').style.visibility = step === 0 ? 'hidden' : 'visible';
  document.getElementById('btn-next').textContent = step === N - 1 ? 'Finish' : 'Continue';
}

async function finish() {
  const ota = document.getElementById('ota');
  if (ota.files.length) {
    if (!ota.files[0].name.endsWith('.bin')) { alert('Must upload a .bin file'); return; }
    uploadFirmware(ota.files[0]);
    return;
  }
  const promises = [];
  document.querySelectorAll('.birthday').forEach(el => {
    if (!el.value) return;
    const [, month, day] = el.value.split('-');
    promises.push(post('/setBirthday', { month, day }));
  });
  promises.push(post('/setDate', { unix: Math.floor(Date.now() / 1000), timezone: document.getElementById('tz').value }));
  await Promise.all(promises);
  location.reload();
}

function uploadFirmware(file) {
  const wrap = document.getElementById('prog-wrap');
  const fill = document.getElementById('prog-fill');
  const pct  = document.getElementById('prog-pct');
  wrap.style.display = 'block';
  const fd = new FormData();
  fd.append('file', file);
  const xhr = new XMLHttpRequest();
  xhr.upload.onprogress = e => {
    const p = Math.floor(e.loaded / e.total * 100);
    fill.style.width = p + '%';
    pct.textContent = p + '%';
  };
  xhr.open('POST', '/update');
  xhr.send(fd);
}

function post(url, data) {
  return fetch(url, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(data) });
}

(function () {
  const sel = document.getElementById('tz');
  for (const k in TZ) {
    const o = document.createElement('option');
    o.value = TZ[k];
    o.textContent = k;
    sel.appendChild(o);
  }
  try {
    const guess = Intl.DateTimeFormat().resolvedOptions().timeZone;
    if (TZ[guess]) sel.value = TZ[guess];
  } catch (e) {}
})();

document.getElementById('add-bday').onclick = () => {
  const row = document.createElement('div');
  row.className = 'brow';
  row.innerHTML = '<input type="date" class="birthday"><button class="rm" onclick="this.parentNode.remove()">&#x2715;</button>';
  document.getElementById('bday-list').appendChild(row);
};
</script>
</body>
</html>
)==";
