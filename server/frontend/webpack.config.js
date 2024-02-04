const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const { NONAME } = require("dns");

module.exports = (env) => {
    return {
        entry: path.join(__dirname, "src", "index.js"),
        output: { path: path.join(__dirname, "dist"), filename: "index.bundle.js" },
        mode: env.dev ? "development" : "production",
        devtool: env.dev ? "source-map" : false,
        resolve: { modules: [path.resolve(__dirname, "src"), "node_modules"] },
        devServer: { 
            static: path.join(__dirname, "src"),
            port: 3000
        },
        module: {
            rules: [
                { 
                    test: /\.(js|jsx)$/, 
                    exclude: /node_modules/, 
                    use: {
                        loader: 'babel-loader',
                        options: {
                            presets: ["@babel/env", "@babel/react"]
                        }
                    } 
                }, 
                {
                    test: /\.css$/i,
                    use: ["style-loader", "css-loader"],
                },
                
            ]
        },
        plugins: [
            new HtmlWebpackPlugin({
                template: path.join(__dirname, "src", "index.html"),
            }),
        ],
    }
};