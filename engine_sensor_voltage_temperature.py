import tempfile
import tabulate
import subprocess


def ahsais_farenheit_poly(x: float):
    return (
        (8.5645 * (x**4))
        - (59.284 * (x**3))
        + (160.76 * (x**2))
        - (245.49 * x)
        + 299.24
    )


def fahrenheit_to_celsius(x: float) -> float:
    return (x - 32) * (5 / 9)


def plot_data(filename: str):
    proc = subprocess.Popen(
        ["gnuplot"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    gnuplot_command = f"""
reset
set terminal png enhanced font 'Verdana,11'
set output 'engine_sensor_voltage_temperature.png'
set title "Engine Sensor Voltage vs Temperature"
set ylabel 'Temp [°C]'
set xlabel 'Voltage [V]'
set xtic auto

set datafile separator ","
plot "{filename}" u 1:2 t "Temperature"
    """
    proc.communicate(gnuplot_command.encode("utf-8"))
    print("Plotted data to engine_sensor_voltage_temperature.png")


table_data = []
with tempfile.NamedTemporaryFile("w") as csvfile:
    for x in reversed(range(0, 30)):
        voltage = x * 0.1
        farenheit = ahsais_farenheit_poly(voltage)
        celsius = fahrenheit_to_celsius(farenheit)
        csvfile.write(f"{voltage},{celsius},{farenheit}\n")
        table_data.append(
            (
                f"{voltage:.2f}V",
                f"{celsius:.2f}°C",
                f"{farenheit:.2f}F",
            )
        )
    csvfile.flush()
    plot_data(csvfile.name)

print(
    tabulate.tabulate(
        table_data,
        headers=["voltage", "°C", "F"],
        tablefmt="github",
    )
)
