import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx } from './test.fixture';
import { ethers } from "ethers";

const contractAddr = "0x054af22e1519b020516d72d749221c24756385c9";
const AMOUNT_TO_DEPOSIT = '345123456789352738273'; // 345.123456789352738273
const recipient = "0xB8c93dF4E1e6b1097889554D9294Dfb42814063a"; //Never use this address for anything other than tests - compromised
const BASE_SCREENS_S = (1 + 2 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE

// Nanos S test
test('[Nano S] Withdraw Tokens with Recipient 18 decimals', zemu("nanos", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function withdraw(uint256, address)']);
  const {data} = await contract.populateTransaction.withdraw(AMOUNT_TO_DEPOSIT, recipient);
  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_withdraw_recipient_18', [BASE_SCREENS_S + 3, 0]);
  await tx;
}));

test('[Nano X] Withdraw Tokens with Recipient 18 decimals', zemu("nanox", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function withdraw(uint256, address)']);
  const {data} = await contract.populateTransaction.withdraw(AMOUNT_TO_DEPOSIT, recipient);

  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_withdraw_recipient_18', [BASE_SCREENS_X + 1, 0]);
  await tx;
}));

test('[Nano SP] Withdraw Tokens with Recipient 18 decimals', zemu("nanosp", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function withdraw(uint256, address)']);
  const {data} = await contract.populateTransaction.withdraw(AMOUNT_TO_DEPOSIT, recipient);

  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanosp_withdraw_recipient_18', [BASE_SCREENS_X + 1, 0]);
  await tx;
}));
