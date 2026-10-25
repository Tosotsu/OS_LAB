# Seminar Report Format Guide (SNMIMT, B.Tech, KTU)

This file describes, exactly, how the 40-page seminar reports in this repository are built: page budget, formatting, chapter structure, writing rules, figure/table rules, references, and a ready-to-compile LaTeX template. Paste it into a new chat together with the four papers and the student's details, and ask for a report "in this format".

**Reference example (final, approved format):** *Neural Radiance Fields (NeRF) in Home and Interior Design*, Sabarinath PS (SNM23CA014), in this repository:

- PDF: `sabarinath_seminar_report/Sabarinath_Seminar_Report.pdf`
- LaTeX source: `sabarinath_seminar_report/report_source.zip` (`main.tex`, `snm.jpg`, `figs/`)
- GitHub: <https://github.com/Tosotsu/OS_LAB/tree/ccr-2324cc80-myjy8s/sabarinath_seminar_report>

> The earlier reports in the repo (Fresher, Akhilesh, Abhinav, Ananda) follow the same structure but still use the older formatting (Computer Modern font, right-aligned page numbers, tighter list spacing). Treat the Sabarinath report as the reference.

---

## 0. Prompt to paste in a new chat

```text
Write a B.Tech seminar report in LaTeX that follows the attached SEMINAR_REPORT_FORMAT.md exactly
(page budget, formatting, header/footer rules, chapter structure, caption rules, IEEE references,
and the LaTeX template in Section 10).

Student: <NAME>, <REG NO>
Seminar guide: <GUIDE NAME>, <DESIGNATION>, Dept. of CSE
Head of the Department: <HOD NAME>, <DESIGNATION>, Dept. of CSE
Seminar coordinator: <COORDINATOR NAME>, <DESIGNATION>, Dept. of CSE
Principal: Dr. Atmaram P
Title: <FULL TITLE>          Short title for page header: <SHORT TITLE>
Declaration date: <DD/MM/YYYY>   Month on title page: <Month YYYY>
Base paper: <paper 1>; other papers: <paper 2>, <paper 3>, <paper 4> (PDFs attached)
Abstract (use word for word): <ABSTRACT>
Total length: exactly 40 PDF pages. Give me the PDF and a zip of main.tex + snm.jpg + figs/.
```

---

## 1. Inputs needed

| Item | Example (reference report) |
|---|---|
| Report title | Neural Radiance Fields (NeRF) in Home and Interior Design |
| Short title (page header) | NeRF in Home and Interior Design |
| Student name, register number | Sabarinath PS, SNM23CA014 |
| Degree line | Bachelor of Technology in Computer Science and Engineering (Artificial Intelligence) |
| Seminar guide | Ms. Lakshmi Anand, Assistant Professor, Dept. of CSE |
| Head of the Department | Ms. Lakshmi Anand, Asst. Professor, Dept. of CSE |
| Seminar coordinator | Ms. Surya T S, Asst. Professor, Dept. of CSE |
| Principal | Dr. Atmaram P |
| Declaration place and date | Maliankara, 23/10/2026 |
| Month on title page | October 2026 |
| Four papers | Paper 1 = base paper; papers 2--4 = related works |
| Abstract | Supplied by the student, used **word for word** |
| College logo | `snm.jpg` |

Department names are written **without** "(Artificial Intelligence)": "Department of Computer Science and Engineering", "Dept. of CSE". Only the **degree** keeps "(Artificial Intelligence)" (title page degree line and certificate degree phrase).

---

## 2. Page budget: exactly 40 PDF pages

| PDF pages | Page | Number shown | Header / footer |
|---|---|---|---|
| 1 | Title page | none | none |
| 2 | Certificate | none | none |
| 3 | Declaration | none | none |
| 4 | Acknowledgement | I (centred) | none |
| 5 | Abstract | II (centred) | none |
| 6--8 | Contents | III--V (centred) | none |
| 9 | List of Figures | VI (centred) | none |
| 10 | List of Tables | VII (centred) | none |
| 11 | List of Abbreviations | VIII (centred) | none |
| 12--39 | Chapters 1--7 (28 pages) | 1--28 (centred) | see Section 4 |
| 40 | References (exactly one page) | 29 (centred) | none |

Target chapter lengths (body = 28 pages):

| Chapter | Pages |
|---|---|
| 1 Introduction | 3 |
| 2 Theoretical Foundations | 4 |
| 3 Literature Survey | 15 (about 3.5 per paper + summary) |
| 4 Discussion and Comparison | 3 |
| 5 Applications | 1 |
| 6 Challenges and Future Directions | 1 |
| 7 Conclusion | 1 |

If the Contents fits on 2 pages, the body gets 29 pages instead. Balance to 40 by trimming or adding text, figures, or a table in Chapters 3--4; never by changing margins, font size, or spacing.

---

## 3. Global formatting

| Property | Value |
|---|---|
| Class | `extreport`, 12 pt, A4 |
| Margins | left 3 cm, right 2 cm, top 3 cm, bottom 3.5 cm |
| Font | **Times New Roman** for text **and** maths: `\usepackage[T1]{fontenc}` + `\usepackage{txfonts}` (load after `amssymb`) |
| Line spacing | **1.5 everywhere** (`\linespread{1.5}`), including abstract, Contents, List of Figures/Tables, abbreviations; only References use 1.15 and the certificate paragraph 1.35 |
| Alignment | Justified (`ragged2e`, `\justifying`) |
| Paragraphs | Each starts with `\paragraph{}` (gives the first-line indent used in the sample) |
| Chapter heading | Centred, bold: "Chapter N" (huge) above the title (Huge); every chapter starts on a new page |
| Section / subsection | Bold, numbered 1.1 and 1.1.1 |
| Figure numbers | By section: Figure 3.1.2 (`\counterwithin{figure}{section}`) |
| Table numbers | By chapter: Table 3.4 |
| Captions | Small font, bold label ("Figure 3.1.2:"), below figures and above tables |
| Front-matter headings | "Acknowledgement", "Declaration", "Abstract" centred huge bold; "Contents", "List of Figures", "List of Tables", "List of Abbreviations" left-aligned huge bold |

---

## 4. Header and footer rules

| Page type | Header | Footer |
|---|---|---|
| Title page, certificate, declaration | none | none (no page number) |
| Acknowledgement to List of Abbreviations | none | centred Roman page number only |
| **Chapter-opening pages** (first page of each chapter) and References | none | centred page number only (no text, no rule) |
| All other chapter pages | left: short title, with a rule below | left: *Dept. of CSE, SNMIMT* (italic); centre: page number; rule above |

---

## 5. Front matter, page by page

1. **Title page**: title (Large bold); "SEMINAR REPORT"; *Submitted by*; name; register number; "to"; "the APJ Abdul Kalam Technological University"; "in partial fulfillment of the requirements for the award of the Degree of"; "Bachelor of Technology"; "in"; degree branch; *Under the guidance of*; guide name, designation, "Dept. of CSE"; college logo; "Department of Computer Science and Engineering"; "SREE NARAYANA MANGALAM INSTITUTE OF / MANAGEMENT AND TECHNOLOGY / MALIANKARA"; month and year. Everything centred and bold, on one page.
2. **Certificate**: department and college heading, logo, "CERTIFICATE", italic certificate paragraph, then Guide (left) and Head of the Department (right) blocks, Coordinator block centred below.
3. **Declaration**: standard declaration paragraph (see template), Place and Date at bottom left, name and register number at bottom right.
4. **Acknowledgement**: God; Principal; HOD (+ "and my seminar guide" if the same person) or separate guide sentence; seminar coordinator; faculty of the department; friends and parents; student name at bottom right.
5. **Abstract**: the student's abstract word for word, split into about three paragraphs, then a bold **Keywords:** line with 8--10 keywords separated by semicolons. One page.
6. **Contents**: chapters, sections, and subsections, at 1.5 spacing.
7. **List of Figures / List of Tables**: one page each. Every entry fits on **one line**, has **no citation**, **no numbers, % or results**.
8. **List of Abbreviations**: two columns (bold abbreviation, expansion), sorted alphabetically, **left-aligned**, 20--25 entries, one page.

---

## 6. Chapter structure

### Chapter 1: Introduction (about 3 pages)
- 2--3 opening paragraphs: the application domain, the core technology, and a paragraph introducing the four papers ("Paper [1], the base paper, by X et al., presents **Name**, which ... Paper [2], by Y et al., presents ...").
- 1.1 General Background (with one overview TikZ figure: inputs → methods → outputs)
- 1.2 Motivation
- 1.3 Problem Statement (one italic paragraph)
- 1.4 Objectives (3 bullets)
- 1.5 Scope
- 1.6 Advantages (4 bullets, each with a bold lead word)
- 1.7 Organization of the Report

### Chapter 2: Theoretical Foundations (about 4 pages)
- Short chapter intro paragraph.
- 6--8 concept sections, with key equations where natural (for example 2.1 representations, 2.2 the core model, 2.3 its successor, 2.4 supporting technique, 2.5 generative models, 2.6 related system, 2.7 Evaluation Metrics).
- One concept-comparison table and one evaluation-metrics table.
- Last section "Taxonomy of Approaches" with a TikZ tree figure placing the four papers.
- No chapter summary section.

### Chapter 3: Literature Survey (about 15 pages)
- One intro paragraph.
- Sections 3.1--3.4, one per paper, titled with the **full paper title**; 3.1 is the base paper.
- Each paper section opens with: authors, institutions, bold method name, one-sentence contribution, and a teaser/overview figure. Then exactly these subsections:
  1. **Problem Statement and Motivation**
  2. **Method** (bold run-in paragraph heads per component, key equations, architecture figure from the paper)
  3. **Experimental Setup** (datasets, metrics, baselines, hardware/runtime)
  4. **Results and Analysis** (main results table with the paper's real numbers, ablation table, optionally one pgfplots chart drawn from the paper's data)
  5. **Discussion** (one paragraph of strengths and limitations)
- 3.5 Summary of the Literature Survey: one table (Work, Venue, Input, Key idea, Output).
- Per paper: 2--3 figures cropped from the paper + 1--2 tables + 0--1 chart.

### Chapter 4: Discussion and Comparison (about 3 pages)
- 4.1 Comparison of Methodologies (big comparison table: paradigm, representation, prior, training, outputs, speed)
- 3 short analysis sections chosen for the topic (for example inputs and representations; editability and completeness; real-time versus offline)
- Strengths and Limitations (table)
- Towards a Combined Workflow (TikZ figure combining the four methods)

### Chapter 5: Applications (1 page)
Four short sections, one paragraph each, citing the relevant papers.

### Chapter 6: Challenges and Future Directions (1 page)
- 6.1 Open Challenges (5 bullets, bold lead words)
- 6.2 Future Directions (5 bullets, bold lead words)

### Chapter 7: Conclusion (1 page)
Three paragraphs: what was covered; one sentence per paper with its key idea; overall takeaway and outlook.

---

## 7. Figure, table, and writing rules

**Captions**
- Short (about 4--9 words), descriptive, title case not required.
- **No numbers, no %, no results** in any caption ("3D-RE-GEN against MIDI and DepR", not "3D-RE-GEN beats MIDI by 0.025 CD").
- Figures taken from a paper are cited in the caption, but the List of Figures must not show the citation:
  `\caption[Overview of the 3D-RE-GEN framework]{Overview of the 3D-RE-GEN framework \cite{p1}}`
- Charts drawn from a paper's numbers: `\caption[Completeness versus number of depth frames]{Completeness versus number of depth frames (data from \cite{p4})}`
- Every List of Figures / List of Tables entry fits on one line.

**Figures**
- Crop figures from the paper PDFs at 200 dpi; never include the paper's own caption text or cut-off text in the crop.
- Widths: full-width diagrams `\textwidth`; tall figures 0.45--0.65 `\textwidth`.
- TikZ diagrams use the template colours (`boxblue`, `boxgray`, `boxgreen`, `boxviolet`) and must not overlap or hyphenate words inside boxes.
- Charts use `seriesA` (baselines) and `seriesB` (the reviewed method).

**Tables**
- `\small`, `\renewcommand{\arraystretch}{1.12}`, full grid (`|l|c|`, `\hline`), bold headers, best value in each column bold, metric arrows (↑/↓) in headers.
- Use `tabularx` with `X` columns for text-heavy tables. No overfull boxes.

**Writing**
- Only real numbers taken from the papers' tables and text; cite every factual claim (`\cite{p1}`).
- Base paper is always `p1`; reviewed papers are `p1`--`p4`.
- Formal third person, consistent British spelling, no first person outside the acknowledgement and declaration.
- Compile with zero undefined references and zero overfull boxes.

---

## 8. References (IEEE style, one page)

- `thebibliography`, line spacing 1.15, heading "References", listed in the Contents.
- Order: [1]--[4] the four reviewed papers (base paper first), then 6--8 foundational works cited in Chapters 1--2. 10--12 references total, all cited in the text, and every citation listed.
- More than four authors: first three + *et al.* Venues abbreviated (Proc. IEEE/CVF CVPR, ICCV, ECCV) to keep the list on one page.

Format and examples (from the reference report):

```text
[1] T. Sautter, J.-N. Dihlmann, and H. Lensch, "3D-RE-GEN: 3D reconstruction of indoor scenes with a
    generative framework," arXiv preprint arXiv:2512.17459, 2025.
[2] Y. Chen, H. T. Nguyen, V. Voleti, V. Jampani, and H. Jiang, "HouseCrafter: Lifting floorplans to 3D
    scenes with 2D diffusion models," in Proc. IEEE/CVF ICCV, 2025, pp. 28440-28449.
[3] H. Matsuki, R. Murai, P. H. J. Kelly, and A. J. Davison, "Gaussian splatting SLAM," in Proc. IEEE/CVF
    CVPR, 2024, pp. 18039-18048.
[4] S. Sun, C. Zhao, Y. Guo, et al., "Behind the veil: Enhanced indoor 3D scene reconstruction with
    occluded surfaces completion," in Proc. IEEE/CVF CVPR, 2025, pp. 12744-12753.
[5] B. Mildenhall, P. P. Srinivasan, M. Tancik, et al., "NeRF: Representing scenes as neural radiance
    fields for view synthesis," in Proc. ECCV, 2020, pp. 405-421.
[6] B. Kerbl, G. Kopanas, T. Leimkuhler, and G. Drettakis, "3D Gaussian splatting for real-time radiance
    field rendering," ACM Trans. Graphics, vol. 42, no. 4, 2023.
[7] R. Rombach, A. Blattmann, D. Lorenz, P. Esser, and B. Ommer, "High-resolution image synthesis with
    latent diffusion models," in Proc. IEEE/CVF CVPR, 2022, pp. 10684-10695.
[8] W. E. Lorensen and H. E. Cline, "Marching cubes: A high resolution 3D surface construction
    algorithm," ACM SIGGRAPH Computer Graphics, vol. 21, no. 4, pp. 163-169, 1987.
```

General IEEE patterns: conference `A. Author, B. Author, and C. Author, "Title," in Proc. Venue, Year, pp. x--y.`; journal `..., "Title," Journal, vol. V, no. N, pp. x--y, Year.`; preprint `..., "Title," arXiv preprint arXiv:XXXX.XXXXX, Year.`

---

## 9. Final checklist

- [ ] Exactly 40 PDF pages; References on one page.
- [ ] Times font for text and maths (`pdffonts` shows only Nimbus Roman / tx fonts).
- [ ] 1.5 line spacing on abstract, Contents, lists, abbreviations, body.
- [ ] Title, certificate, declaration: no header, footer, or page number.
- [ ] Chapter-opening pages and References: only a centred page number.
- [ ] Other chapter pages: header (short title + rule) and footer (*Dept. of CSE, SNMIMT*, centred number, rule).
- [ ] Department names without "(Artificial Intelligence)"; degree line keeps it.
- [ ] Abstract is the student's text word for word.
- [ ] List of Figures/Tables: one line each, no citations, no numbers or %.
- [ ] Abbreviations alphabetical and left-aligned.
- [ ] All numbers match the papers; every claim cited; every reference cited.
- [ ] No undefined references, no overfull boxes, no overlapping diagram labels.
- [ ] Deliver the PDF and a zip of `main.tex`, `snm.jpg`, `figs/` that compiles on its own.

---

## 10. LaTeX template (compiles as is)

Replace every `<<...>>` placeholder. Compile with `pdflatex` three times. Needs `snm.jpg` next to `main.tex` and figures in `figs/`.

```latex
\documentclass[12pt,a4paper,final]{extreport}
\usepackage[utf8]{inputenc}
\usepackage[T1]{fontenc}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{txfonts}            % Times New Roman for text and maths (after amssymb)
\usepackage{bm}
\usepackage{array}
\usepackage{setspace}
\usepackage{multirow}
\usepackage{caption}
\usepackage{subcaption}
\usepackage{ragged2e}
\justifying
\usepackage{tabularx}
\usepackage{booktabs}
\usepackage{float}
\usepackage{longtable}
\usepackage[table]{xcolor}
\renewcommand{\bibname}{References}
\usepackage[colorlinks]{hyperref}
\hypersetup{linkcolor={black},citecolor={black},urlcolor={black}}
\usepackage{graphicx}
\usepackage[left=3cm,right=2cm,top=3cm,bottom=3.5cm]{geometry}
\linespread{1.5}
\usepackage{titlesec}
\usepackage{fancyhdr}
\setlength{\headheight}{15pt}
\usepackage{enumitem}
\setlist{itemsep=2pt,topsep=4pt,parsep=0pt}
\usepackage{tikz}
\usetikzlibrary{arrows.meta,positioning,shapes.geometric,fit,calc,backgrounds}
\usepackage{pgfplots}
\pgfplotsset{compat=1.18}
\pgfplotsset{every axis/.append style={x tick label style={text height=1.6ex, text depth=0.35ex}}}

% Chart and diagram colours
\definecolor{seriesA}{HTML}{2A78D6}   % baselines
\definecolor{seriesB}{HTML}{EB6834}   % reviewed method
\definecolor{seriesC}{HTML}{1BAF7A}
\definecolor{seriesD}{HTML}{EDA100}
\definecolor{gridgray}{HTML}{D9D9D6}
\definecolor{inkgray}{HTML}{52514E}
\definecolor{boxblue}{HTML}{E3EEFB}
\definecolor{boxorange}{HTML}{FCE8DE}
\definecolor{boxgreen}{HTML}{DFF3EA}
\definecolor{boxgray}{HTML}{F1F1EF}
\definecolor{boxviolet}{HTML}{E9E6F7}

% Float placement: let text fill pages
\renewcommand{\topfraction}{0.85}
\renewcommand{\bottomfraction}{0.7}
\renewcommand{\textfraction}{0.1}
\renewcommand{\floatpagefraction}{0.75}
\setcounter{topnumber}{3}
\setcounter{bottomnumber}{2}
\setcounter{totalnumber}{4}
\setlength{\textfloatsep}{14pt plus 4pt minus 4pt}
\setlength{\floatsep}{12pt plus 4pt minus 2pt}
\setlength{\intextsep}{12pt plus 4pt minus 2pt}
\captionsetup{font=small,labelfont=bf,skip=6pt}
\raggedbottom
\setlength{\emergencystretch}{2.5em}
\makeatletter
\renewcommand*\l@figure{\@dottedtocline{1}{1.5em}{3.3em}}
\makeatother

% Figure numbers by section (Figure 3.1.2)
\usepackage{chngcntr}
\counterwithin{figure}{section}
\renewcommand{\thefigure}{\thesection.\arabic{figure}}

% Headings (front-matter style; chapters are redefined after the front matter)
\titleformat{\chapter}[display]
{\normalfont\rmfamily\huge\bfseries\color{black}}
{\chaptertitlename\ \thechapter}{20pt}{\huge}
\titleformat{\section}
{\normalfont\rmfamily\normalsize\bfseries\color{black}}
{\thesection}{16pt}{\large}
\titleformat{\subsection}
{\normalfont\rmfamily\small\bfseries\color{black}}
{\thesubsection}{16pt}{\normalsize}
\titlespacing{\chapter}{0pc}{0pc}{.5pc}
\titlespacing{\section}{0pc}{.8pc}{.2pc}
\titlespacing{\subsection}{0pc}{.8pc}{.1pc}

\begin{document}

% ================= TITLE PAGE (no header/footer/number) =================
\begin{titlepage}
    \centering
    \pagenumbering{gobble}
    {\Large\textbf{<<TITLE>>}} \\
    \vspace*{0.4 cm}
    {\large\textbf{SEMINAR REPORT}} \\
    \vspace*{0.7cm}
    {\emph{Submitted by}}\\[0.2cm]
    \textbf{<<NAME>>}\\
    \textbf{<<REGNO>>}\\
    \textbf{to}\\
    \textbf{the APJ Abdul Kalam Technological University}\\
    \textbf{in partial fulfillment of the requirements for the award of the Degree of}\\
    \textbf{Bachelor of Technology}\\
    \textbf{in}\\
    \textbf{Computer Science and Engineering (Artificial Intelligence)}\\
    \vspace*{0.7cm}
    {\textit{Under the guidance of}} \\[0.15cm]
    \textbf{<<GUIDE>>} \\
    \textbf{<<GUIDE DESIGNATION>>} \\
    \textbf{Dept. of CSE} \\
    \vspace*{0.6cm}
    \includegraphics[scale=0.42]{snm.jpg} \\
    \vspace*{.6cm}
    \textbf{Department of Computer Science and Engineering} \\
    \textbf{SREE NARAYANA MANGALAM INSTITUTE OF}\\
    \textbf{MANAGEMENT AND TECHNOLOGY}\\
    \textbf{MALIANKARA}\\
    \vspace*{0.8cm}
    <<MONTH YEAR>>
    \vfill
\end{titlepage}

% ================= CERTIFICATE =================
\clearpage
\thispagestyle{empty}
\begin{center}
{\fontsize{13}{16}\selectfont \textbf{DEPARTMENT OF COMPUTER SCIENCE \& ENGINEERING}}\\[10pt]
{\fontsize{13}{16}\selectfont \textbf{SREE NARAYANA MANGALAM INSTITUTE OF MANAGEMENT \&\\TECHNOLOGY, MALIANKARA}}\\[14pt]
\includegraphics[scale=0.32]{snm.jpg}\\[10pt]
\textbf{\Large CERTIFICATE}
\end{center}
\vspace{4pt}
\begingroup\setstretch{1.35}
\noindent\emph{This is to certify that the seminar report entitled {\bf <<TITLE>>} submitted by {\bf <<NAME>>} ({\bf <<REGNO>>}), to the {\bf Department of Computer Science and Engineering, SNM Institute of Management and Technology, Maliankara}, in partial fulfilment of the requirement for the award of B.Tech Degree in Computer Science and Engineering (Artificial Intelligence) is a bonafide record of the work carried out by the student.}\par
\endgroup
\vspace{1.8cm}
\noindent
\begin{minipage}[t]{0.48\textwidth}
\centering
\textbf{Guide}\\[28pt]
\textbf{<<GUIDE>>}\\
\textbf{Asst. Professor}\\
\textbf{Dept. of CSE}
\end{minipage}%
\hfill
\begin{minipage}[t]{0.48\textwidth}
\centering
\textbf{Head of the Department}\\[28pt]
\textbf{<<HOD>>}\\
\textbf{Asst. Professor}\\
\textbf{Dept. of CSE}
\end{minipage}
\vspace{1.1cm}

\noindent
\begin{minipage}[t]{\textwidth}
\centering
\textbf{Coordinator}\\[28pt]
\textbf{<<COORDINATOR>>}\\
\textbf{Asst. Professor}\\
\textbf{Dept. of CSE}
\end{minipage}
\newpage

% ================= DECLARATION =================
\thispagestyle{empty}
\begin{center}
\begin{huge}
\textbf{Declaration}
\end{huge}
\end{center}
\vskip0.5cm
I undersigned hereby declare that the seminar report \textbf{<<TITLE>>}, submitted for partial fulfilment of the requirements for the award of degree of Bachelor of Technology of the APJ Abdul Kalam Technological University, Kerala is a bonafide work done by me under the supervision of \textbf{<<GUIDE>>}. This submission represents my ideas in my own words and where ideas or words of others have been included, I have adequately and accurately cited and referenced the original sources. I also declare that I have adhered to ethics of academic honesty and integrity and have not misrepresented or fabricated any data or idea or fact or source in my submission. I understand that any violation of the above will be a cause for disciplinary action by the institute and/or the University and can also evoke penal action from the sources which have thus not been properly cited or from whom proper permission has not been obtained. This report has not been previously formed the basis for the award of any degree, diploma or similar title of any other University.

\vspace{2cm}
\noindent
\begin{minipage}[t]{0.5\textwidth}
Place: Maliankara\\
Date: <<DD/MM/YYYY>>
\end{minipage}%
\hfill
\begin{minipage}[t]{0.4\textwidth}
\centering
\textbf{<<NAME>>}\\
\textbf{<<REGNO>>}
\end{minipage}
\newpage

% ================= ACKNOWLEDGEMENT (page I) =================
\thispagestyle{plain}
\pagenumbering{Roman}
\setcounter{page}{1}
\addcontentsline{toc}{chapter}{Acknowledgement}
\begin{center}
\begin{huge}
\textbf{Acknowledgement}
\end{huge}
\end{center}
\vskip1cm
\hspace*{1 cm} Firstly, I thank God, the Almighty, with whose blessings, this seminar has been successfully completed.

I wish to give deep sense of acknowledgement to our Principal \textbf{Dr. Atmaram P}, for his constant encouragement and valuable advice throughout the course.

I am extremely grateful to \textbf{<<HOD>>}, Head of the Department of Computer Science and Engineering and my seminar guide, for the valuable guidance through this humble endeavor. The highly enterprising attitude, patience for listening to my doubts, timely suggestions and guidance made my seminar a so-called reality in stipulated time.
I would also like to thank our seminar coordinator \textbf{<<COORDINATOR>>}, Assistant Professor, Department of Computer Science and Engineering, for the gracious encouragement and the valuable assistance.

I express my sincere gratitude to all the faculty members of the department of Computer Science and Engineering for their co-operation and support to the seminar.

I also express my sincere gratitude to all my friends and my parents for their co-operation and constant inspiration.

\vspace{2cm}
\noindent\hfill
\begin{minipage}[t]{0.4\textwidth}
\centering
\textbf{<<NAME>>}
\end{minipage}
\newpage

% ================= ABSTRACT (page II) =================
\begin{center}
\begin{huge}
\textbf{Abstract}
\end{huge}
\end{center}
\addcontentsline{toc}{chapter}{Abstract}
\vskip0.3cm
\paragraph{} <<ABSTRACT PARAGRAPH 1>>

\paragraph{} <<ABSTRACT PARAGRAPH 2>>

\paragraph{} <<ABSTRACT PARAGRAPH 3>>

\vspace{0.5cm}
\noindent
\textbf{Keywords:} <<Keyword 1>>; <<Keyword 2>>; <<Keyword 3>>.
\newpage

% ================= CONTENTS AND LISTS (1.5 spacing) =================
\thispagestyle{plain}
\tableofcontents
\listoffigures
\addcontentsline{toc}{chapter}{List of Figures}
\listoftables
\addcontentsline{toc}{chapter}{List of Tables}

% ================= LIST OF ABBREVIATIONS (left-aligned) =================
\chapter*{List of Abbreviations}
\addcontentsline{toc}{chapter}{List of Abbreviations}
\setlength{\LTleft}{0pt}\setlength{\LTright}{\fill}
\begin{longtable}{p{2.6cm}l}
\textbf{<<ABBR1>>} & <<Expansion 1>> \\
\textbf{<<ABBR2>>} & <<Expansion 2>> \\
\end{longtable}
\newpage

% ================= PAGE STYLE FOR THE CHAPTERS =================
\lhead{<<SHORT TITLE>>}
\chead{}
\rhead{}
\lfoot{\textit{Dept. of CSE, SNMIMT}}
\cfoot{\thepage}
\rfoot{}
\renewcommand{\headrulewidth}{0.4pt}
\renewcommand{\footrulewidth}{0.4pt}
\pagestyle{fancy}
\fancypagestyle{plain}{%          % chapter-opening pages: centred number only
  \fancyhf{}%
  \cfoot{\thepage}%
  \renewcommand{\headrulewidth}{0pt}%
  \renewcommand{\footrulewidth}{0pt}}
\titleformat{\chapter}[display]
  {\normalfont\huge\bfseries\filcenter}
  {\chaptername\ \thechapter}{1ex}{\Huge}
\titlespacing*{\chapter}{0pt}{-10pt}{24pt}
\pagenumbering{arabic}
\setcounter{page}{1}

% ================= CHAPTER 1 =================
\chapter{Introduction}
\paragraph{} <<Opening paragraph>> \cite{p1}.

\section{General Background}
\paragraph{} <<Text>>

% Figure cropped from a paper: citation in caption, not in List of Figures
% \begin{figure}[htbp]
% \centering
% \includegraphics[width=\textwidth]{figs/p1_framework.png}
% \caption[Overview of the framework]{Overview of the framework \cite{p1}}
% \label{fig:p1_framework}
% \end{figure}

% Results table: short caption, real numbers, best values bold
{\renewcommand{\arraystretch}{1.12}
\begin{table}[htbp]
\centering
\caption{<<Method>> against baselines}\label{tab:p1_main}
\small
\begin{tabular}{|l|c|c|}
\hline
\textbf{Method} & \textbf{Metric A $\uparrow$} & \textbf{Metric B $\downarrow$} \\ \hline
Baseline & 0.70 & 0.036 \\ \hline
<<Method>> & \textbf{0.85} & \textbf{0.011} \\ \hline
\end{tabular}
\end{table}}

% ... Sections 1.2 to 1.7, then Chapters 2 to 7 as in Section 6 of the guide ...

% ================= REFERENCES (one page, IEEE) =================
\begingroup
\setstretch{1.15}
\begin{thebibliography}{99}
\addcontentsline{toc}{chapter}{References}

\bibitem{p1}
A. Author, B. Author, and C. Author, ``Title of the base paper,'' in \textit{Proc. IEEE/CVF CVPR}, 2025, pp. 1--10.

\end{thebibliography}
\endgroup

\end{document}
```
