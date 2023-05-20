dataSets = [
    {
        name: "Vanilla FO2",
        getPath: function(file) {
            return `csv_vanilla/${file}_vanilla.csv`;
        }
    },
    {
        name: "ECCO (0.6.2)",
        getPath: function(file) {
            return `csv_ecco_06/${file}.csv`;
        }
    },
];