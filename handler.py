from colorama import Fore as F, Style as S
from os import system
from os.path import exists
from time import time
from platform import system as platform_name
import matplotlib.pyplot as plt

from config import cfg, j2
# from lib import sorts, utils


def handle(c: list[str], settings_link: dict[str, ...]):
    try:
        if len(c) == 0:
            return


        if c[0] == 'menu':
            print(F.CYAN + "== MENU ==")
            print(F.LIGHTBLUE_EX + "exit")
            print(F.LIGHTBLUE_EX + "menu")
            print(F.LIGHTBLUE_EX + "help [<command>]")
            print(F.LIGHTBLUE_EX + "settings read | set <key> <value>")
            print(F.LIGHTBLUE_EX + "call <call-string>")
            print(F.LIGHTBLUE_EX + " > binary <variable_type> <value>")
            print(F.LIGHTBLUE_EX + " > overflow")
            print(F.LIGHTBLUE_EX + " > infinite_cycle")
            print(F.LIGHTBLUE_EX + " > render <filename> <scale_type> [<color>]")
            print(F.LIGHTBLUE_EX + " > combine {<filename_1> <filename_2> ...} <scale_type> {<color_1> <color_2> ...}")
            print(F.LIGHTBLUE_EX + " > script <filename>")
            print()
            print()

        elif c[0] == 'help':
            if len(c) > 1:
                command = ' '.join(c[1:])
                if command == 'exit':
                    print(F.CYAN + S.NORMAL + "turns off the program")
                elif command == 'menu':
                    print(F.CYAN + S.NORMAL + "prints a menu (as above)")
                elif command == 'help':
                    print(F.YELLOW + S.BRIGHT + "this", F.CYAN + S.NORMAL + "page")
                elif command == 'settings':
                    print(F.CYAN + S.NORMAL + "operations with project settings: reading/rewriting values")
                elif command == 'call':
                    print(F.CYAN + S.NORMAL + "calls a script or a command:")

                    print(F.CYAN + S.DIM + " >", F.CYAN + S.BRIGHT + "binary")
                    print(F.GREEN + S.DIM + "  > " + S.NORMAL + "prints bits of given number (in given digital format)")

                    print(F.CYAN + S.DIM + " >", F.CYAN + S.BRIGHT + "overflow")
                    print(F.GREEN + S.DIM + "  > " + S.NORMAL + "tries to overflow a float by multiplication by 10")

                    print(F.CYAN + S.DIM + " >", F.CYAN + S.BRIGHT + "infinite_cycle")
                    print(F.GREEN + S.DIM + "  > " + S.NORMAL + "tries to overflow a float with adding a 1")

                    print(F.CYAN + S.DIM + " >", F.CYAN + S.BRIGHT + "render")
                    print(F.GREEN + S.DIM + "  > " + S.NORMAL + "renders a plot from a datafile with given name and parameters")

                    print(F.CYAN + S.DIM + " >", F.CYAN + S.BRIGHT + "combine")
                    print(F.GREEN + S.DIM + "  > " + S.NORMAL + "renders a plot from 2 or more datafile with given names and parameters")

                    print(F.CYAN + S.DIM + " >", F.CYAN + S.BRIGHT + "script")
                    print(F.GREEN + S.DIM + "  > " + S.NORMAL + "loads prepared script from a file")
            else:
                print(F.CYAN + S.NORMAL + "use", F.YELLOW + S.BRIGHT + "help <command>", F.CYAN + S.NORMAL + "to see info")

        elif c[0] == 'settings':
            if c[1] == 'read':
                print(F.LIGHTBLACK_EX + S.NORMAL + str(cfg.PATH.SETTINGS))
                print(F.LIGHTBLACK_EX + S.NORMAL + str(settings_link))
            elif c[1] == 'set':
                key = c[2]
                if key in settings_link.keys():
                    value = ' '.join(c[3:])
                    if value == 'false':
                        value = False
                    elif value == 'true':
                        value = True
                    elif value == 'none' or value == 'null':
                        value = None
                    else:
                        try:
                            value = int(value)
                        except:
                            try:
                                value = eval(value)
                            except:
                                raise ValueError("parsing error")
                    if type(value) is type(settings_link[key]) or value is None or settings_link[key] is None:
                        settings_link[key] = value
                        with open(cfg.PATH.SETTINGS, 'w', encoding='utf8') as f:
                            f.write(j2.to_(settings_link))
                        print(F.LIGHTBLACK_EX + S.NORMAL + "> setting updated")
                    else:
                        print(F.RED + S.DIM + "> bad types")
                else:
                    raise KeyError("key was not found")
            else:
                raise ValueError("unknown argument")


        elif c[0] == 'call':
            if len(c) < 2:
                raise IndexError("not enough args")

            if c[1] == 'binary':
                type_ = c[2].lower()
                if type_ not in ("f", "u", "float", "uint", "unsigned"):
                    raise ValueError("unable to parse given type")

                is_float = False
                if type_ in ("f", "float"):
                    is_float = True

                value = float(c[3]) if is_float else int(c[3])

                with open("data/binary_input.csv", 'w') as csv:
                    print('f' if is_float else 'u', value, file=csv)

                if platform_name() == 'Linux':
                    system(f"./{cfg.PATH.BIN_local}binary")
                elif platform_name() == 'Windows':
                    system(f"{cfg.PATH.BIN_local}binary.exe")
                else:
                    print(F.RED + S.DIM + "> current platform is not supported... yet...")
                    exit()

            if c[1] == 'overflow':
                if platform_name() == 'Linux':
                    system(f"./{cfg.PATH.BIN_local}overflow")
                elif platform_name() == 'Windows':
                    system(f"{cfg.PATH.BIN_local}overflow.exe")
                else:
                    print(F.RED + S.DIM + "> current platform is not supported... yet...")
                    exit()

            if c[1] == 'infinite_cycle':
                if platform_name() == 'Linux':
                    system(f"./{cfg.PATH.BIN_local}infinite_cycle")
                elif platform_name() == 'Windows':
                    system(f"{cfg.PATH.BIN_local}infinite_cycle.exe")
                else:
                    print(F.RED + S.DIM + "> current platform is not supported... yet...")
                    exit()

            if c[1] == 'render':
                filename = c[2]
                scale = c[3].lower()
                color = c[4] if len(c) > 4 else '#fa8072'

                print(F.LIGHTBLACK_EX + "reading a datafile...")
                with open(filename) as csv:
                    legend = list(map(lambda s: s.replace('_', ' '), csv.readline().strip()[1:].split('\t')))
                    x, y = list(), list()
                    for line in csv.readlines():
                        line = line.split(',')
                        x.append(int(line[0]))
                        y.append(int(line[1]))

                print(F.LIGHTBLACK_EX + "rendering...")
                plt.figure(figsize=(settings_link["plot_fig_x"], settings_link["plot_fig_y"]))
                plt.scatter(x, y, color=color, s=settings_link["plot_dot_size"])
                plt.xscale(scale)
                plt.yscale(scale)
                plt.title(legend[0])
                plt.xlabel(legend[1])
                plt.ylabel(legend[2])
                plt.grid(True, alpha=.3)
                save_file = filename.replace('.csv', '')
                while exists(save_file + '.png'):
                    save_file += '(1)'
                save_file += '.png'
                plt.savefig(save_file)
                plt.close()
                print(F.GREEN + "Successfully saved at", F.YELLOW + S.DIM + save_file)

            elif c[1] == 'combine':
                i = 2
                filenames = [c[i][1:]]
                i += 1
                while i < len(c) and c[i].count('}') == 0:
                    filenames.append(c[i])
                    i += 1
                filenames.append(c[i][:-1])
                if len(filenames) < 2:
                    raise IndexError("less than 2 subplots")

                i += 1
                scale = c[i].lower()
                i += 1
                colors = [c[i][1:]] + c[i+1:i+len(filenames)-1] + [c[i+len(filenames)-1][:-1]]

                plt.figure(figsize=(settings_link["plot_fig_x"], settings_link["plot_fig_y"]))

                with open(filenames[0]) as csv:
                    global_legend = list(map(lambda s: s.replace('_', ' '), csv.readline().strip()[1:].split('\t')))
                    x_global, y = list(), list()
                    for line in csv.readlines():
                        line = line.split(',')
                        x_global.append(int(line[0]))
                        y.append(int(line[1]))
                print(F.LIGHTBLACK_EX + f"rendering #{0}: x_global={len(x_global)}, y={len(y)}")
                plt.scatter(x_global, y, color=colors[0], s=settings_link["plot_dot_size"], label=global_legend[0])

                for j in range(1, len(filenames)):
                    with open(filenames[j]) as csv:
                        legend = list(map(lambda s: s.replace('_', ' '), csv.readline().strip()[1:].split('\t')))
                        y = list()
                        for line in csv.readlines():
                            line = line.split(',')
                            y.append(int(line[1]))
                    print(F.LIGHTBLACK_EX + f"rendering #{j}: [x_global], y={len(y)}")
                    plt.scatter(x_global, y, color=colors[j], s=settings_link["plot_dot_size"], label=legend[0])
                plt.xscale(scale)
                plt.yscale(scale)
                plt.title("merged plots")
                plt.legend()
                plt.xlabel(global_legend[1])
                plt.ylabel(global_legend[2])
                plt.grid(True, alpha=.3)
                save_file = f"combined_{int(time())}"
                while exists(save_file + '.png'):
                    save_file += '(1)'
                save_file += '.png'
                plt.savefig(save_file)
                plt.close()
                print(F.GREEN + "Successfully saved at", F.YELLOW + S.DIM + save_file)

            elif c[1] == 'script':
                filename = ' '.join(c[2:])
                if not exists(filename):
                    filename += '.scrpt'
                with open(filename, encoding='utf8') as script:
                    for line in script.readlines():
                        line = line.strip()
                        print(F.LIGHTBLACK_EX + "$ received:", line)
                        handle(line.split(), settings_link)

        else:
            raise ValueError("parsing failed")

        print()
    except Exception as e:
        args = list(e.args)
        print(
            F.RED + S.DIM + "something went wrong:",
            F.YELLOW + S.NORMAL + f"[{e.__class__.__name__}]: \"{', '.join(list(map(str, args))) if len(args) > 0 else '<no args>'}\""
        )
