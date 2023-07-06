import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, nano_models, txFromEtherscan} from './test.fixture';

const BASE_SCREENS_S = 4
const BASE_SCREENS_X = 4

// Original TX: https://etherscan.io/tx/0xe2ee1f6921ecfdcaa7a059aec194eb446812e031ff904717ff923eaec357d482
nano_models.forEach(function(model) {
  test('[Nano ' + model.letter + '] ETH Zapper', zemu(model, async (sim, eth) => {
    const serializedTx = txFromEtherscan("0x02f87a018201b3843b9aca00850342770c008304689894d1791428c38e25d459d5b01fb25e942d4ad83a258803311fc80a57000084d0e30db0c001a0ee16cb7242fd6eed7d404ae760ff34aa03a6487c8a11bb655a3e7c150abcba29a04a832a84c11131bacaf66e24a14e8fd33b7a3d35174e3e674e2a6d7c34ca37f5");
    const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);
    const right_clicks = model.letter === 'S' ? BASE_SCREENS_S : BASE_SCREENS_X;
    await waitForAppScreen(sim);
    await sim.navigateAndCompareSnapshots('.', model.name + '_zap_eth', [right_clicks, 0]);
    await tx;
  }));
});
