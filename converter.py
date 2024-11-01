import subprocess
import os
import glob

def convert_svg_to_tikz(svg_file, tex_file):
    command = f"svg2tikz {svg_file} > {tex_file}"
    subprocess.run(command, shell=True)

def clean_folder():
    command = "rm *.aux, *.fdb_latexmk, *.fls, *.log, *.pdf, *.gz"
    subprocess.run(command, shell=True)

def replace_text_in_tex(tex_file):
    with open(tex_file, 'r', encoding='utf-8') as file:
        tex_content = file.read()

    updated_tex_content = tex_content.replace("\n\\documentclass{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage{tikz}\n\n\\begin{document}\n\n\n\\def \\globalscale {1.000000}\n", "\\begin{figure}\n\\centering\n", 1)
    updated_tex_content = updated_tex_content.replace("\end{document}", "\n\\caption{}\n\\label{img:}\n\n\\end{figure}", 1)
    updated_tex_content = updated_tex_content.replace("text=black,anchor=south", "text=black,anchor=south,fit={(0,0) (3.175, 1.5875)}")

    with open(tex_file, 'w', encoding='utf-8') as file:
        file.write(updated_tex_content)

if __name__ == "__main__":
    svg_dir = "./doc/charts/"

    # svg_files = glob.glob(os.path.join(svg_dir, "*.svg"))

    svg_files = ["./doc/charts/lambert_spot.svg"]

    for svg_file in svg_files:
        tex_file = svg_file.replace(".svg", ".tex")

        convert_svg_to_tikz(svg_file, tex_file)
        replace_text_in_tex(tex_file)

    clean_folder()