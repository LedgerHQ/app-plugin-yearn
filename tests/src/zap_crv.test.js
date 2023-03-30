import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, nano_models, txFromEtherscan} from './test.fixture';

const BASE_SCREENS_S = (1 + 1 + 1 + 1 + 1)
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1)

nano_models.forEach(function(model) {
  test('[Nano ' + model.letter + '] CRV Zapper', zemu(model, async (sim, eth) => {
    // Original TX: https://etherscan.io/tx/0xe2fb7aebb9df20533a1f2a154ee6267cbb3204d3c44cc0cbf1ad3643ace5c847
    const serializedTx = txFromEtherscan("0x"+"02f90111012c8477359400850737be76008303b36f9401d7f32b6e463c96c00575fa97b8224326c6a6b980b8a451787905000000000000000000000000d533a949740bb3306d119cc777fa900ba034cd5200000000000000000000000027b5739e22ad9033bcbf192059122d163b60349d000000000000000000000000000000000000000000000005d315730295b0d800000000000000000000000000000000000000000000000004ea2ded8950ae416900000000000000000000000065215710313f9599d1e8f41ab6af66fc44276c75c080a0b846aad9bed078425eb4991fdcde597469b5cda604e5e07edaf0f3c43b1d60d9a01c605cd16f7fea66f5acabf2c1118d942601c87bb7b8a33cd5007d732252b937");

    const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);
    const right_clicks = model.letter === 'S' ? BASE_SCREENS_S : BASE_SCREENS_X;
    await waitForAppScreen(sim);
    await sim.navigateAndCompareSnapshots('.', model.name + '_zap_crv', [right_clicks, 0]);
    await tx;
  }));
});
