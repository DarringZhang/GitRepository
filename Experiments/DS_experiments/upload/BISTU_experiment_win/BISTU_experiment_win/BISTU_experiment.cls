\LoadClass{article}
\RequirePackage{xeCJK}
\RequirePackage{ctex}
\RequirePackage{graphicx}
\RequirePackage{geometry}
\RequirePackage{titlesec}
\RequirePackage{fancyhdr}
\RequirePackage{enumitem}
\RequirePackage{listings}
\RequirePackage{xcolor}
\usepackage{color}

\linespread{1.2}


%设置图表的题注相关
\renewcommand\thesection{\chinese{section}、}
\renewcommand\thesubsection{\arabic{subsection}}
\renewcommand\thesubsubsection{(\arabic{subsubsection})}

%\renewcommand{\normalsize}{\fontsize{11pt}{\baselineskip}\selectfont}

\newlist{clause}{enumerate}{1}
\setlist[clause]{fullwidth,itemindent=2em,label=(\arabic*)}


%设置中文字体  WIN
\setCJKmainfont [BoldFont = 黑体, ItalicFont = 仿宋 ]  {宋体}
\setCJKsansfont [BoldFont = 黑体] {黑体}
\setCJKmonofont {宋体}

% \setCJKfamilyfont {song} {simsun}
% \newcommand{\song}{\CJKfamily{song}} 
% \setCJKfamilyfont {hei}  {msyh}
% \newcommand{\hei}{\CJKfamily{hei}} 
% \setCJKfamilyfont {fangsong}   {simfang}
% \newcommand{\fsong}{\CJKfamily{fangsong}} 

%字号
\newcommand{\chuhao}{\fontsize{42pt}{\baselineskip}\selectfont}     %初号  
\newcommand{\xiaochuhao}{\fontsize{36pt}{\baselineskip}\selectfont} %小初号  
\newcommand{\yihao}{\fontsize{28pt}{\baselineskip}\selectfont}      %一号  
\newcommand{\erhao}{\fontsize{21pt}{\baselineskip}\selectfont}      %二号  
\newcommand{\xiaoerhao}{\fontsize{18pt}{\baselineskip}\selectfont}  %小二号  
\newcommand{\sanhao}{\fontsize{15.75pt}{1.5\baselineskip}\selectfont}  %三号  
\newcommand{\sihao}{\fontsize{14pt}{\baselineskip}\selectfont}       %四号  
\newcommand{\xiaosihao}{\fontsize{12pt}{\baselineskip}\selectfont}  %小四号  
\newcommand{\wuhao}{\fontsize{10.5pt}{\baselineskip}\selectfont}    %五号  
\newcommand{\xiaowuhao}{\fontsize{9pt}{\baselineskip}\selectfont}   %小五号  
\newcommand{\liuhao}{\fontsize{7.875pt}{\baselineskip}\selectfont}  %六号  
\newcommand{\qihao}{\fontsize{5.25pt}{\baselineskip}\selectfont}    %七号


\geometry{top=1in,bottom=1in,left=1in,right=1in}
\setcounter{secnumdepth}{3}
\titleformat*{\section}{\Large\bfseries}
\titleformat*{\subsection}{\large\bfseries}
\titleformat*{\subsubsection}{\large}
\titleformat{\section}{\Large\bfseries}{\thesection}{2pt}{}
\titleformat{\subsection}{\large\bfseries}{\arabic{section}.\thesubsection}{1em}{}

\graphicspath{{figures/}{figure/}{pictures/}%
{picture/}{pic/}{pics/}{image/}{images/}}

\titlespacing{\subsection}{0em}{*2}{*0.1}
\titlespacing{\subsubsection}{0em}{*1}{*1}
\titlespacing{\section}{0em}{*4}{*2}

\definecolor{dkgreen}{rgb}{0,0.6,0}
\definecolor{gray}{rgb}{0.5,0.5,0.5}
\definecolor{comment}{rgb}{0.56,0.64,0.68}

\lstset{
  frame=tb,
  aboveskip=3mm,
  belowskip=3mm,
  xleftmargin=2em,
  xrightmargin=2em,
  showstringspaces=false,
  columns=flexible,
  framerule=1pt,
  rulecolor=\color{gray!35},
  backgroundcolor=\color{gray!5},
  basicstyle={\small\ttfamily},
  numbers=none,
  numberstyle=\tiny\color{gray},
  keywordstyle=\color{blue},
  commentstyle=\color{comment},
  stringstyle=\color{dkgreen},
  breaklines=true,
  breakatwhitespace=true,
  tabsize=2,
}

\pagestyle{fancy}
\lhead{实验名称：\newtitle}
\chead{姓名：\name}
\rhead{学号：\stuid}
